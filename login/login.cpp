#include "login.h"
#include "ui_login.h"


#include <QPushButton>

login::login(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::loginClass)
{
	ui->setupUi(this);
	this->chat = new chatWidget;
	this->connnectInit();
}

login::~login()
{

}

void login::connnectInit()
{
	connect(ui->btn_login, &QPushButton::clicked, this, &login::loginSucceed);

}

void login::loginSucceed()
{
	this->hide();
	chat->show();

}
