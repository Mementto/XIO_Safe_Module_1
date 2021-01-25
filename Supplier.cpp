#include "Supplier.h"

Supplier::Supplier(): mId(-1), mPath(""), mCriticalArea(nullptr) {}

Supplier::~Supplier() {

	/* 停止当前线程 */
	terminate();

	/* 等待上述操作完成 */
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
	/* 通过路径获取相机的capture */
	VideoCapture capture(mPath);
	if (!capture.isOpened()) {
		cout << "视频流创建失败" << endl;
		//qDebug() << "视频流创建失败" << endl;
	} else {
		cout << "视频流创建成功" << endl;
		//qDebug() << "视频流创建成功" << endl;

		mCriticalArea->getQMutex_3().lock();
		mCriticalArea->getVideoCapture()->insert(pair<int, VideoCapture>(mId, capture));
		mCriticalArea->getQMutex_3().unlock();
	}
}
