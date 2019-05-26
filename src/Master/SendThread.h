#ifndef SENDTHREAD_H
#define SENDTHREAD_H

#include <QObject>

class SendThread : public QObject
{
	Q_OBJECT

public:
	SendThread(QObject *parent = nullptr);
	~SendThread();

public:
	void sendRun();			//线程入口函数

private:
	
};

#endif // SENDTHREAD_H
