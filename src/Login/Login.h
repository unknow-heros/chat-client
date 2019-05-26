/*
 *       登陆界面
*/
#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "Comment/LineEditWithButton.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr );
    ~Login();

signals:
	void signClose();					//关闭程序信号
	void signLoginSuccess();			//登陆成功信号
	void signLoginFailed();				//登陆失败信号

private:
    void initUI();         //ui init
    void initAction();    //信号与槽初始化

    void loginClose();        //win close
    void loginStart();					//开始登陆

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
