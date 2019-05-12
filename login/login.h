/*
 *       登陆界面
*/


#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "General/LineEditWithButton.h"

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr );
    ~login();

private:
    void uiInit();         //ui init
    void connectInit();    //信号与槽初始化
    void gui_init();        //gui初始化



    void loginClose();        //win close
private:
	//MainWindow *m_main_ptr_ = NULL;
    void loginStart();					//开始登陆

private:
    Ui::login *ui;

signals:
	void signClose();					//关闭程序信号
	void signLoginSuccess();			//登陆成功信号
	void signLoginFailed();				//登陆失败信号
};

#endif // WIDGET_H
