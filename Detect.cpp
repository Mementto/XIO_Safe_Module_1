#include "Detect.h"

Detect::Detect(): 
	mConfigFileName("config.ini"),
	mCofigSection("program_entrance_param"),
	mKeyCameraNum("camera_num"),
	mKeyHandlerNum("handler_num"),
	mKeyBufferSize1("buffer_size_1"),
	mKeyBufferSize2("buffer_size_2"),
	mKeyLessNum("less_num"),
	mCameraSection("camera_wifi_path") {

}

Detect::~Detect() {

}

void Detect::process() {
	createThread();
}

void Detect::createThread() {
	CParseIniFile cParseIniFile;
	map<string, string> params;
	cParseIniFile.ReadConfig(mConfigFileName, params, mCofigSection);
	int cameraNum = stoi(params.find(mKeyCameraNum)->second);
	int handlerNum = stoi(params.find(mKeyHandlerNum)->second);
	int bufferSize1 = stoi(params.find(mKeyBufferSize1)->second);
	int bufferSize2 = stoi(params.find(mKeyBufferSize2)->second);
	int lessNum = stoi(params.find(mKeyLessNum)->second);

	StartAllThread* startAllThread = new StartAllThread(mConfigFileName,
		mCameraSection, cameraNum, 
		handlerNum, bufferSize1, 
		bufferSize2, lessNum);

	startAllThread->start();
}