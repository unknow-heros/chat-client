#ifndef RECVTHREAD_H
#define RECVTHREAD_H

#include <QObject>

class RecvThread : public QObject
{
	Q_OBJECT

public:
	RecvThread(QObject *parent = nullptr);
	~RecvThread();

public:
	void recvRun();			//�߳���ں���

private:
	
};

#endif // RECVTHREAD_H
