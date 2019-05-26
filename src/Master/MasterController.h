/*
	主逻辑控制模块
*/


#ifndef MASTERCONTROLLER_H
#define MASTERCONTROLLER_H

#include <QWidget>
#include <QThread>

class Login;
class chatWidget;
class RecvThread;
class SendThread;
class interviewWidget;

class MasterController : public QWidget
{
	Q_OBJECT

public:
	MasterController(QWidget *parent = nullptr);
	~MasterController();

	enum windows
	{
		LOGIN_WIN = 0,								//login界面
		CHAT_WIN  = 1,								//聊天界面
		INTERVIEW = 2,								//面试界面
	};

public:
	void winShow(windows win);						//window显示控制模块
	void close();

private:
	void initUI();									//初始化所有的UI
	void initAction();								//初始化信号槽

	void threadInit();								//线程初始化
	void threadCloseAll();							//退出所有线程

	void loginSuccess();							//登陆成功
	
public:
	QThread * m_threadSend = NULL;					//发送线程
	SendThread * m_send    = NULL;

	QThread * m_threadRecv = NULL;					//接收线程
	RecvThread * m_recv    = NULL;	


private:
	Login *	m_loginWindow	= NULL;					//登陆界面
	chatWidget * m_chatWindow = NULL;				//聊天界面
	interviewWidget * m_interviewWindow = NULL;		//面试界面

signals:	
	void sendThreadStart();							//发送线程启动信号
	void recvThreadStart();							//接收线程启动信号

};

#endif  // MASTERCONTROLLER_H
