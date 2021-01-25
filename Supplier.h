#ifndef __SUPPLIER__
#define __SUPPLIER__

#include "CriticalArea.h"

class Supplier: public QThread {
public:

	Supplier();

	~Supplier();

	/**************************************************

	Function:setPath

	Description:从GUIMain中获取摄像头路径

	Calls:null

	Input:path，通过此路径找到每一个摄像头。

	Output:null

	Others:null

	**************************************************/
	void setPath(string path);

	/**************************************************

	Function:setId

	Description:从GUIMain中获取摄像头编号

	Calls:null

	Input:id，通过此编号来区分imshow窗口（imshow窗
		  口的窗口名字必须不同），但是该id跟随线程
		  的开启经过栈和队列，一直到窗口显示，需要
		  用到map，操作复杂，是否有更好的办法。

	Output:null

	Others:null

	**************************************************/
	void setId(int id);

	/**************************************************

	Function:setData

	Description:从GUIMain中获取指向临界区的指针

	Calls:null

	Input:data，通过此获取临界区所有数据

	Output:null

	Others:null

	**************************************************/
	void setData(CriticalArea* data);

	void run();

private:

	/* 指向临界区的指针 */
	CriticalArea* mCriticalArea;

	/* 摄像头路径 */
	string mPath;

	/* 摄像头编号 */
	int mId;
};

#endif // !__SUPPLIER__