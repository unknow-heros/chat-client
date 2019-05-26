#ifndef PERSON_H
#define PERSON_H

#include <QWidget>
#include "ui_person.h"

class person : public QWidget
{
	Q_OBJECT

public:
	person(QWidget *parent = 0);
	~person();
public:
	void setUserName(const QString& uName);			//�����ǳ�
	void setSignName(const QString& sName);			//���ø���ǩ��
	void setHeadImage(const QString & head);		//����ͷ��

	QString getUserName();
private:
	QString m_headFile;		//�û�ͷ��
	QString m_uName;		//�û�����						
	QString m_sName;		//�û�����ǩ��

	Ui::person *ui;
};

#endif // PERSON_H
