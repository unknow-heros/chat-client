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
	void sendRun();			//�߳���ں���

private:
	
};

#endif // SENDTHREAD_H
