#include "StartAllThread.h"

StartAllThread::StartAllThread(
	const string& fileName,
	const string& section,
	const int& cameraNum,
	const int& windowNum,
	const int& bufferSize_1,
	const int& bufferSize_2,
	const int& lessNum)
	: mWindowNum(windowNum),
	mFileName(fileName),
	mSection(section),
	mCameraNum(cameraNum) {

	mCParseIniFile = new CParseIniFile();
	mCriticalArea = new CriticalArea(bufferSize_1, bufferSize_2, 0, 0, lessNum);
	mProducer = new Producer[cameraNum];
	mConsumer = new Consumer[windowNum];
	mSupplier = new Supplier[cameraNum];
	mTestClass = new TestClass(mCriticalArea);
}

void StartAllThread::run() {
	map<string, string> mPath;

	/* 将ini文件中的指定键-值对输出到map中 */
	mCParseIniFile->ReadConfig(mFileName, mPath, mSection);
	map<string, string>::iterator iter;

	/* 根据path中的键-值对数量来确定创建的生产者线程数
	（上面的windowNum并没有用到，只是用来确定数组的范围） */
	for (iter = mPath.begin(); iter != mPath.end(); iter++) {
		mSupplier[stoi(iter->first)].setData(mCriticalArea);
		mSupplier[stoi(iter->first)].setPath(iter->second);
		mSupplier[stoi(iter->first)].setId(stoi(iter->first));
		mSupplier[stoi(iter->first)].start();
	}

	clock_t start, end;
	start = clock();
	map<int, VideoCapture>::iterator iter_1;
	//do {
	//	mCriticalArea->getQMutex_3().lock();
	//	if (mCriticalArea->getVideoCapture()->size() > 0) {
	//		for (iter_1 = mCriticalArea->getVideoCapture()->begin();
	//			iter_1 != mCriticalArea->getVideoCapture()->end(); iter_1++) {

	//			mProducer->setData(mCriticalArea);
	//			mProducer->setId(iter_1->first);
	//			mProducer->setVideoCapture(iter_1->second);
	//			mProducer->start();
	//			cout << iter_1->first << endl;
	//		}

	//		for (iter_1 = mCriticalArea->getVideoCapture()->begin(); 
	//			iter_1 != mCriticalArea->getVideoCapture()->end();) {
	//			mCriticalArea->getVideoCapture()->erase(iter_1++);
	//		}
	//	}

	//	mCriticalArea->getQMutex_3().unlock();
	//	end = clock();
	//} while (end - start < 20000);

	while (mCriticalArea->getVideoCapture()->size() != 5);

	delete[] mSupplier;
	mSupplier = nullptr;

	for (iter_1 = mCriticalArea->getVideoCapture()->begin();
		iter_1 != mCriticalArea->getVideoCapture()->end(); iter_1++) {

		mProducer[iter_1->first].setData(mCriticalArea);
		mProducer[iter_1->first].setId(iter_1->first);
		mProducer[iter_1->first].setVideoCapture(iter_1->second);
		mProducer[iter_1->first].start();
	}

	/* 根据windowNum确定消费者线程数 */
	for (size_t i = 0; i < mWindowNum; i++) {
		mConsumer[i].setData(mCriticalArea);
		mConsumer[i].start();
	}

	mTestClass->start();
}

StartAllThread::~StartAllThread() {

	/* 停止当前线程 */
	quit();

	/* 等待上述操作完成 */
	wait();

	delete[] mProducer;
	delete[] mConsumer;
	delete mCriticalArea;
	delete mCParseIniFile;
	mProducer = nullptr;
	mConsumer = nullptr;
	mCriticalArea = nullptr;
	mCParseIniFile = nullptr;
}