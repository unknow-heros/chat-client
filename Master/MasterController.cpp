#include "MasterController.h"
#include "login.h"
#include "chatWidget.h"
#include "VideoVM/interviewWidget.h"
#include "SendThread.h"
#include "RecvThread.h"

MasterController::MasterController(QWidget *parent)
	: QWidget(parent)
{
	this->uiInit();
	this->connectInit();
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
	case MasterController::INTERVIEW:  this->m_interviewWindow->show();
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

void MasterController::uiInit()
{
	if (this->m_loginWindow ==NULL)
	{
		this->m_loginWindow = new login;
	}

	if (this->m_chatWindow == NULL)
	{
		this->m_chatWindow = new chatWidget;
	}
	
	if (this->m_interviewWindow == NULL )
	{
		this->m_interviewWindow = new interviewWidget;
	}


	this->m_loginWindow->show();
}

void MasterController::connectInit()
{
	//登陆界面信号与槽
	connect(this->m_loginWindow, &login::signClose, this, &MasterController::close);
	connect(this->m_loginWindow, &login::signLoginSuccess, this, &MasterController::loginSuccess);
	connect(this->m_chatWindow, &chatWidget::interviewShow, this, &MasterController::interviewVideo);
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

void MasterController::interviewVideo()
{
	this->m_interviewWindow->show();
}
