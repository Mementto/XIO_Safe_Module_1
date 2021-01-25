#include "Supplier.h"

Supplier::Supplier(): mId(-1), mPath(""), mCriticalArea(nullptr) {}

Supplier::~Supplier() {

	/* ֹͣ��ǰ�߳� */
	terminate();

	/* �ȴ������������ */
	wait();
}

void Supplier::setPath(string path) {
	mPath = path;
}

void Supplier::setId(int id) {
	mId = id;
}

void Supplier::setData(CriticalArea* data) {
	mCriticalArea = data;
}

void Supplier::run() {
	/* ͨ��·����ȡ�����capture */
	VideoCapture capture(mPath);
	if (!capture.isOpened()) {
		cout << "��Ƶ������ʧ��" << endl;
		//qDebug() << "��Ƶ������ʧ��" << endl;
	} else {
		cout << "��Ƶ�������ɹ�" << endl;
		//qDebug() << "��Ƶ�������ɹ�" << endl;

		mCriticalArea->getQMutex_3().lock();
		mCriticalArea->getVideoCapture()->insert(pair<int, VideoCapture>(mId, capture));
		mCriticalArea->getQMutex_3().unlock();
	}
}
