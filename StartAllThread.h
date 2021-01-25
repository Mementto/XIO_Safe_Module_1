#ifndef __STARTALLTHREAD__
#define __STARTALLTHREAD__

#include "Producer.h"
#include "Consumer.h"
#include "Supplier.h"
#include "TestClass.h"
#include "CParseIniFile.h"
#include "CriticalArea.h"
#include <time.h>

class StartAllThread :public QThread {

public:
	/**************************************************

		Function:StartAllThread

		Description:���캯������ʼ����Ա����

		Calls:null

		Input:fileName�������ļ����ļ���

			  section�������ļ��Ľ���

			  cameraNum��������������ޣ���ʼ��������
			  ָ������Ĵ�С���������̵߳������Լ����
			  �����������ļ��еļ�-ֵ������ȷ����

			  windowNum����ʼ��������ָ������Ĵ�С��
			  ȷ���������߳�����

			  bufferSize_1��1���ٽ�����������С

			  bufferSize_2��2���ٽ�����������С

			  lessNum��Ϊ�˷�ֹ��������ͼƬ�洢�ռ�ͬ
			  ʱ����������ͼƬ�洢�ռ�����Ҫ����ѭ��
			  ɾ��ͼƬ����ͼƬ�洢�ռ�Ҫ��С����û�
			  ������С��LessNumΪ��С�ڵ���

		Output:null

		Others:����ͨ��Ա������ʼ������ָ���Ա������
		�ٶѿռ�

	**************************************************/
	StartAllThread(
		const string& fileName,
		const string& section,
		const int& cameraNum,
		const int& windowNum,
		const int& bufferSize_1,
		const int& bufferSize_2,
		const int& lessNum);

	/**************************************************

	Function:~StartAllThread()

	Description:����������delete����ָ��ѵ�ָ��

	Calls:null

	Input:null

	Output:null

	Others:null

	**************************************************/
	~StartAllThread();

	/**************************************************

	Function:run

	Description:�����������̺߳��������߳�

	Calls:Producer�࣬setData(CriticalArea* data)��
		  setPath(string path)��setId(int id)��
		  run()

		  Consumer�࣬setData(CriticalArea* data)��
		  run()

	Input:null

	Output:null

	Others:null

	**************************************************/
	void run();

private:

	/**/
	Supplier* mSupplier;

	/* �����ߣ�������ж�ȡ�������ٽ���ջͼƬ���߳�ָ�� */
	Producer* mProducer;

	/* �����ߣ����ٽ���ջ�ж�ȡ��������Զ��е��߳�ָ�� */
	Consumer* mConsumer;

	/**/
	TestClass* mTestClass;

	/* ָ���ٽ��������б�����ָ�� */
	CriticalArea* mCriticalArea;

	/* ��ȡini�����ļ���Ϣ���ָ�� */
	CParseIniFile* mCParseIniFile;

	/* ��ʼ��������ָ������Ĵ�С��ȷ���������߳����� */
	const int mWindowNum;

	/* ������������ޣ���ʼ��������ָ��
	����Ĵ�С���������̵߳������Լ����
	�����������ļ��еļ�-ֵ������ȷ���� */
	const int mCameraNum;

	/* �����ļ����ļ��� */
	const string mFileName;

	/* �����ļ��Ľ��� */
	const string mSection;

	/* �������ļ��ļ�-ֵ�ԣ������ڿ纯����¼�������߳��� */
	map<int, string> mPath;

};

#endif // !__STARTALLTHREAD__