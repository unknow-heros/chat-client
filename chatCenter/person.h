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
	void setUserName(const QString& uName);			//设置昵称
	void setSignName(const QString& sName);			//设置个性签名
	void setHeadImage(const QString & head);		//设置头像
private:
	QString m_headFile;		//用户头像
	QString m_uName;		//用户名称						
	QString m_sName;		//用户个性签名

	Ui::person *ui;
};

#endif // PERSON_H
