#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);

    this->setWindowTitle("onLine");
    this->resize(450,600);

    this->uiInit();
    this->connectInit();
    this->gui_init();       //gui init
}

login::~login()
{
    delete ui;
}

void login::uiInit()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->btn_return->hide();
    //ui->tip->hide();
    //ui->tip_2->hide();
}


void login::connectInit()
{
	
	connect(this, &login::destroyed, this, &login::loginClose);		//右上角关闭按钮
	connect(ui->btn_login, &QPushButton::clicked, this, &login::loginStart);
	
	connect(ui->btn_accunt_next,&QPushButton::clicked,[=]{
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

	connect(ui->btn_email_prev,&QPushButton::clicked,[=](){
		ui->stackedWidget->setCurrentIndex(1);
	});
	 connect(ui->btn_email_next,&QPushButton::clicked,[=](){
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
	connect(ui->btn_return,&QPushButton::clicked,[=](){
		ui->stackedWidget->setCurrentIndex(0);
		ui->btn_return->hide();
	});
}

//gui init
void login::gui_init()
{
    
}


//win close
void login::loginClose()
{
	emit signClose();
}


void login::loginStart()
{
	emit signLoginSuccess();
}


