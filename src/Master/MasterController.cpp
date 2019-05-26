#include "MasterController.h"
#include "Login/Login.h"
#include "Chat/chatWidget.h"
#include "SendThread.h"
#include "RecvThread.h"

MasterController::MasterController(QWidget *parent)
	: QWidget(parent)
{
	this->initUI();
	this->initAction();
}

MasterController::~MasterController()
{
	delete this->m_loginWindow;
	this->m_loginWindow = NULL;

	delete this->m_chatWindow;
	this->m_chatWindow = NULL;

	delete this->m_interviewWindow;
	this->m_interviewWindow = NULL;
	
}

//
void MasterController::winShow(windows win)
{
	switch (win)
	{
	case MasterController::LOGIN_WIN: this->m_loginWindow->show();
		break;
	case MasterController::CHAT_WIN:  this->m_chatWindow->show();
		break;
	default:
		break;
	}
}

//关闭程序
void MasterController::close()
{
	this->threadCloseAll();
}

void MasterController::initUI()
{
	if (this->m_loginWindow ==NULL)
	{
		this->m_loginWindow = new Login;
	}

	if (this->m_chatWindow == NULL)
	{
		this->m_chatWindow = new chatWidget;
	}
	
	this->m_loginWindow->show();
}

void MasterController::initAction()
{
	//登陆界面信号与槽
	connect(this->m_loginWindow, &Login::signClose, this, &MasterController::close);
	connect(this->m_loginWindow, &Login::signLoginSuccess, this, &MasterController::loginSuccess);
}

//线程初始化
void MasterController::threadInit()
{
	if (this->m_threadSend == NULL)
	{
		this->m_threadSend = new QThread(this);
		this->m_send = new SendThread;
		m_send->moveToThread(m_threadSend);
		connect(this, &MasterController::sendThreadStart, m_send, &SendThread::sendRun);
		this->m_threadSend->start();
	}
	
	if (this->m_threadRecv == NULL)
	{
		this->m_threadRecv = new QThread(this);
		this->m_recv = new RecvThread;
		m_recv->moveToThread(m_threadRecv);
		connect(this, &MasterController::recvThreadStart, m_recv, &RecvThread::recvRun);
		this->m_threadSend->start();
	}
}

//关闭所有子线程
void MasterController::threadCloseAll()
{
	if (this->m_threadSend != NULL)
	{
		this->m_threadSend->quit();		//线程退出
		this->m_threadSend->wait();		//等待线程退出

		delete this->m_threadSend;
		delete this->m_send;

		this->m_threadSend = NULL;
		this->m_send = NULL;
	}

	if (this->m_threadRecv != NULL)
	{
		this->m_threadRecv->quit();		//线程退出
		this->m_threadRecv->wait();		//等待线程退出

		delete this->m_threadRecv;
		delete this->m_recv;

		this->m_threadRecv = NULL;
		this->m_recv = NULL;
	}
}

void MasterController::loginSuccess()
{
	this->m_loginWindow->hide();
	this->winShow(CHAT_WIN);
}
