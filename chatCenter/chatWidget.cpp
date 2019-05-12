#include "chatWidget.h"
#include "ui_chatWidget.h"

#include <QDebug>

chatWidget::chatWidget(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::chatWidget)
{
	ui->setupUi(this);

	this->connectInit();

	//ui->stackedWidget->setCurrentIndex(0);
}

chatWidget::~chatWidget()
{

}

void chatWidget::connectInit()
{
	connect(ui->btn_personal, &QPushButton::clicked, this,&chatWidget::switchWin);
	
}

void chatWidget::switchWin()
{
	qDebug() << "send show";
	emit interviewShow();

}
