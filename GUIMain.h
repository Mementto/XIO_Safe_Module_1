/**************************************************

Copyright:

Author:韩俊博

Date:2021/1/19

Description:启动生产者线程和消费者线程，
            并接收来自2号临界区队列中的图片帧。

**************************************************/

#ifndef __GUIMAIN__
#define __GUIMAIN__
#include "Producer.h"
#include "Consumer.h"
#include "CParseIniFile.h"
#include "CriticalArea.h"

class GUIMain {
public:

	/**************************************************

	Function:GUIMain

	Description:构造函数，初始化成员变量

	Calls:null

	Input:fileName，配置文件的文件名
	      
		  section，配置文件的节名

		  cameraNum，相机数量的上限，初始化生产者
		  指针数组的大小（生产者线程的数量以及相机
		  数量由配置文件中的键-值数量对确定）

		  windowNum，初始化消费者指针数组的大小并
		  确定消费者线程数量

		  bufferSize_1，1号临界区缓冲区大小

		  bufferSize_2，2号临界区缓冲区大小

		  lessNum，为了防止缓冲区和图片存储空间同
		  时满而阻塞（图片存储空间满后要进行循环
		  删除图片），图片存储空间要略小与可用缓
		  冲区大小。LessNum为略小于的量

	Output:null

	Others:对普通成员变量初始化，对指针成员变量开
	辟堆空间

	**************************************************/
	GUIMain(
		const string& fileName,
		const string& section,
		const int& cameraNum,
		const int& windowNum,
		const int& bufferSize_1,
		const int& bufferSize_2,
		const int& lessNum);

	/**************************************************

	Function:~GUIMain()

	Description:析构函数，delete所有指向堆的指针

	Calls:null

	Input:null

	Output:null

	Others:null

	**************************************************/
	virtual ~GUIMain();

	/**************************************************

	Function:create

	Description:启动生产者线程和消费者线程

	Calls:Producer类，setData(CriticalArea* data)、
		  setPath(string path)、setId(int id)、
		  run()

		  Consumer类，setData(CriticalArea* data)、
		  run()

	Input:null

	Output:null

	Others:null

	**************************************************/
	void create();

	/**************************************************

	Function:imageShow

	Description:接收来自2号临界区队列中的图片帧

	Calls:CriticalArea类，getQMutex_2()、
		  getNumUsedBytes_2()、getFull_2()、
		  getTestStream()、getNumUsedBytes_1()、
		  getEmpty_2()

	Input:null

	Output:null

	Others:null

	**************************************************/
	void imageShow();
private:

	/* 生产者：从相机中读取并存入临界区栈图片的线程指针 */
	Producer* mProducer;

	/* 消费者：从临界区栈中读取并存入测试队列的线程指针 */
	Consumer* mConsumer;

	/* 指向临界区中所有变量的指针 */
	CriticalArea* mCriticalArea;

	/* 获取ini配置文件信息类的指针 */
	CParseIniFile* mCParseIniFile;

	/* 初始化消费者指针数组的大小并确定消费者线程数量 */
	const int mWindowNum;

	/* 配置文件的文件名 */
	const string mFileName;

	/* 配置文件的节名 */
	const string mSection;
};

#endif // !__GUIMAIN__
