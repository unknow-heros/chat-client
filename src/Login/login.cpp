#include "Login.h"
#include "ui_Login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    this->setWindowTitle("onLine");
    this->resize(450,600);

    this->initUI();
    this->initAction();
}

Login::~Login()
{
    delete ui;
}

void Login::initUI()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->returnBtn->hide();
    //ui->tip->hide();
    //ui->tip_2->hide();
}


void Login::initAction()
{
	
	connect(this, &Login::destroyed, this, &Login::loginClose);		//右上角关闭按钮
	connect(ui->loginBtn, &QPushButton::clicked, this, &Login::loginStart);
	
	connect(ui->accuntNextBtn,&QPushButton::clicked,[=]{
       //check the accunt is normal
       if(true)
       {
           ui->stackedWidget->setCurrentIndex(2);
       }
       else
       {
           ui->tip->show();
       }
	});

	connect(ui->emailPrevBtn,&QPushButton::clicked,[=](){
		ui->stackedWidget->setCurrentIndex(1);
	});
	 connect(ui->emailNextBtn,&QPushButton::clicked,[=](){
		//check the email is normal
       if(true)
       {
           ui->stackedWidget->setCurrentIndex(3);
       }
		else
		{
           ui->tip_2->show();
		}
	});
	connect(ui->returnBtn,&QPushButton::clicked,[=](){
		ui->stackedWidget->setCurrentIndex(0);
		ui->returnBtn->hide();
	});
}

//win close
void Login::loginClose()
{
	emit signClose();
}

void Login::loginStart()
{
	emit signLoginSuccess();
}


