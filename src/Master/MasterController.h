/*
	���߼�����ģ��
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
		LOGIN_WIN = 0,								//login����
		CHAT_WIN  = 1,								//�������
		INTERVIEW = 2,								//���Խ���
	};

public:
	void winShow(windows win);						//window��ʾ����ģ��
	void close();

private:
	void initUI();									//��ʼ�����е�UI
	void initAction();								//��ʼ���źŲ�

	void threadInit();								//�̳߳�ʼ��
	void threadCloseAll();							//�˳������߳�

	void loginSuccess();							//��½�ɹ�
	
public:
	QThread * m_threadSend = NULL;					//�����߳�
	SendThread * m_send    = NULL;

	QThread * m_threadRecv = NULL;					//�����߳�
	RecvThread * m_recv    = NULL;	


private:
	Login *	m_loginWindow	= NULL;					//��½����
	chatWidget * m_chatWindow = NULL;				//�������
	interviewWidget * m_interviewWindow = NULL;		//���Խ���

signals:	
	void sendThreadStart();							//�����߳������ź�
	void recvThreadStart();							//�����߳������ź�

};

#endif  // MASTERCONTROLLER_H