/**************************************************

Copyright:

Author:韩俊博

Date:2021/1/19

Description:CriticalArea的功能实现源文件

**************************************************/

#include "CriticalArea.h"

CriticalArea::CriticalArea(const int& buffer_1, const int& buffer_2, const int& bytes_1, const int& bytes_2, const int& lessNum)
	: mBufferSize_1(buffer_1), mBufferSize_2(buffer_2), 
	mNumUsedBytes_1(bytes_1), mNumUsedBytes_2(bytes_2), mLessNum(lessNum),
	mVideoStream(new stack<map<int, Mat>*>), mTestStream(new queue<map<int, Mat>*>) {}

CriticalArea::~CriticalArea() {}

int& CriticalArea::getNumUsedBytes_1() {
	return mNumUsedBytes_1;
}
int& CriticalArea::getNumUsedBytes_2() {
	return mNumUsedBytes_2;
}
int& CriticalArea::getBufferSize_1() {
	return mBufferSize_1;
}
int& CriticalArea::getBufferSize_2() {
	return mBufferSize_2;
}
int CriticalArea::getClearThreshold_1() {
	int temp = mBufferSize_1;
	return temp - mLessNum;
}
int CriticalArea::getClearThreshold_2() {
	int temp = mBufferSize_2;
	return temp - mLessNum;
}
stack<map<int, Mat>*>* CriticalArea::getVideoStream() {
	return mVideoStream;
}
queue<map<int, Mat>*>* CriticalArea::getTestStream() {
	return mTestStream;
}
QWaitCondition& CriticalArea::getEmpty_1() {
	return mBufferEmpty_1;
}
QWaitCondition& CriticalArea::getFull_1() {
	return mBufferFull_1;
}
QWaitCondition& CriticalArea::getEmpty_2() {
	return mBufferEmpty_2;
}
QWaitCondition& CriticalArea::getFull_2() {
	return mBufferFull_2;
}
QMutex& CriticalArea::getQMutex_1() {
	return mQMutex_1;
}
QMutex& CriticalArea::getQMutex_2() {
	return mQMutex_2;
}
