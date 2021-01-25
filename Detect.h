#ifndef __DETECT__
#define __DETECT__
#include <iostream>
#include "CParseIniFile.h"
#include "StartAllThread.h"

class Detect {
public:
	Detect();
	void process();
	~Detect();
private:
	void createThread();
	const string mConfigFileName;
	const string mCofigSection;
	const string mKeyCameraNum;
	const string mKeyHandlerNum;
	const string mKeyBufferSize1;
	const string mKeyBufferSize2;
	const string mKeyLessNum;
	const string mCameraSection;
};

#endif // !__DETECT__