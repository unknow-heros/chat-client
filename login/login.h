#ifndef LOGIN_H
#define LOGIN_H
#include "chatWidget.h"
#include <QtWidgets/QWidget>
#include "ui_login.h"

namespace Ui {
	class login;
}

class login : public QWidget
{
	Q_OBJECT

public:
	explicit login(QWidget *parent = 0);
	~login();

public:
	void connnectInit();		//信号与槽初始化
	void loginSucceed();		//登陆成功
private:
	Ui::loginClass *ui;
	chatWidget * chat;
};

#endif // LOGIN_H
