#ifndef __SUPPLIER__
#define __SUPPLIER__

#include "CriticalArea.h"

class Supplier: public QThread {
public:

	Supplier();

	~Supplier();

	/**************************************************

	Function:setPath

	Description:��GUIMain�л�ȡ����ͷ·��

	Calls:null

	Input:path��ͨ����·���ҵ�ÿһ������ͷ��

	Output:null

	Others:null

	**************************************************/
	void setPath(string path);

	/**************************************************

	Function:setId

	Description:��GUIMain�л�ȡ����ͷ���

	Calls:null

	Input:id��ͨ���˱��������imshow���ڣ�imshow��
		  �ڵĴ������ֱ��벻ͬ�������Ǹ�id�����߳�
		  �Ŀ�������ջ�Ͷ��У�һֱ��������ʾ����Ҫ
		  �õ�map���������ӣ��Ƿ��и��õİ취��

	Output:null

	Others:null

	**************************************************/
	void setId(int id);

	/**************************************************

	Function:setData

	Description:��GUIMain�л�ȡָ���ٽ�����ָ��

	Calls:null

	Input:data��ͨ���˻�ȡ�ٽ�����������

	Output:null

	Others:null

	**************************************************/
	void setData(CriticalArea* data);

	void run();

private:

	/* ָ���ٽ�����ָ�� */
	CriticalArea* mCriticalArea;

	/* ����ͷ·�� */
	string mPath;

	/* ����ͷ��� */
	int mId;
};

#endif // !__SUPPLIER__