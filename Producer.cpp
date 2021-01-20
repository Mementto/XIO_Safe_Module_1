/**************************************************

Copyright:

Author:������

Date:2021/1/19

Description:Producer�Ĺ���ʵ��Դ�ļ�

**************************************************/

#include "Producer.h"

Producer::Producer() : mPath(""), mId(-1), mData(nullptr) {}

Producer::~Producer() {}

void Producer::setPath(string path) {
	mPath = path;
}

void Producer::setId(int id) {
	mId = id;
}

void Producer::setData(CriticalArea* data) {
	mData = data;
}

void Producer::run() {

	/* ͨ��·����ȡ�����capture */
	VideoCapture capture(mPath);
	if (!capture.isOpened()) {
		cout << "error!" << endl;
	} else {
		while (true) {
			Mat frame;

			/* ��captureѭ������Mat֡�� */
			capture >> frame;
			if (frame.empty()) {
				break;
			}

			/* ��1���ٽ������� */
			mData->getQMutex_1().lock();

			/* ���2���ٽ����Ļ������Ƿ����� */
			while (mData->getNumUsedBytes_1() == mData->getBufferSize_1()) {

				/* ������������ȴ���������Ϊ���ڸ��̵߳ȴ�ʱ�����ñ���̼߳���
				ʹ�ø��ٽ�����һֱ���п���ռ��������������һ�� */
				mData->getEmpty_1().wait(&mData->getQMutex_1());
			}

			/* �ж�1���ٽ�����ջ�����Ƿ�ﵽ���ޣ����������Լ�����С�ڻ����������� */
			if (mData->getVideoStream()->size() > mData->getClearThreshold_1()) {

				/* ���ջ */
				while (mData->getVideoStream()->size() > 0) {

					/* ע�⣬ջ��ȫ��ָ�򿪱ٶѿռ��ָ�룬
					pop���Ժ���񲻹��ã�����delete */
					delete mData->getVideoStream()->top();
					mData->getVideoStream()->top() = nullptr;
					mData->getVideoStream()->pop();

					/* 1���ٽ����������������ݼ���һ�� */
					--mData->getNumUsedBytes_1();
				}
			}
			map<int, Mat> *item = new map<int, Mat>;

			/* ��Mat֡����map�У�������Գ��Ե�������
			һ���࣬ר��������װMat������int�����ţ� */
			item->insert(pair<int, Mat>(mId, frame));

			/* ��mapѹջ */
			mData->getVideoStream()->push(item);

			/* 1���ٽ���������������������һ�� */
			++mData->getNumUsedBytes_1();

			/* ���������ڡ��ȴ�1���ٽ��������ݡ����߳� */
			mData->getFull_1().wakeAll();

			/* ����1���ٽ��� */
			mData->getQMutex_1().unlock();
		}
	}
}