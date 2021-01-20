/**************************************************

Copyright:

Author:韩俊博

Date:2021/1/19

Description:Producer的功能实现源文件

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

	/* 通过路径获取相机的capture */
	VideoCapture capture(mPath);
	if (!capture.isOpened()) {
		cout << "error!" << endl;
	} else {
		while (true) {
			Mat frame;

			/* 将capture循环输入Mat帧中 */
			capture >> frame;
			if (frame.empty()) {
				break;
			}

			/* 对1号临界区加锁 */
			mData->getQMutex_1().lock();

			/* 检查2号临界区的缓冲区是否已满 */
			while (mData->getNumUsedBytes_1() == mData->getBufferSize_1()) {

				/* 若已满则解锁等待（解锁是为了在该线程等待时可以让别的线程继续
				使用该临界区）一直到有空余空间则加锁并进行下一步 */
				mData->getEmpty_1().wait(&mData->getQMutex_1());
			}

			/* 判断1号临界区的栈容量是否达到上限（该上限由自己定，小于缓冲区容量） */
			if (mData->getVideoStream()->size() > mData->getClearThreshold_1()) {

				/* 清空栈 */
				while (mData->getVideoStream()->size() > 0) {

					/* 注意，栈中全是指向开辟堆空间的指针，
					pop了以后好像不管用，还得delete */
					delete mData->getVideoStream()->top();
					mData->getVideoStream()->top() = nullptr;
					mData->getVideoStream()->pop();

					/* 1号临界区缓冲区可用数据减少一个 */
					--mData->getNumUsedBytes_1();
				}
			}
			map<int, Mat> *item = new map<int, Mat>;

			/* 将Mat帧存入map中（这里可以尝试单独开辟
			一个类，专门用来封装Mat变量和int相机编号） */
			item->insert(pair<int, Mat>(mId, frame));

			/* 将map压栈 */
			mData->getVideoStream()->push(item);

			/* 1号临界区缓冲区可用数据增加一个 */
			++mData->getNumUsedBytes_1();

			/* 唤醒所有在“等待1号临界区有数据”的线程 */
			mData->getFull_1().wakeAll();

			/* 解锁1号临界区 */
			mData->getQMutex_1().unlock();
		}
	}
}