#include "chatWidget.h"
#include "ui_chatWidget.h"

#include <QDebug>

chatWidget::chatWidget(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::chatWidget)
{
	ui->setupUi(this);

	this->initAction();

	//ui->stackedWidget->setCurrentIndex(0);
}

chatWidget::~chatWidget()
{

}

void chatWidget::initAction()
{
	connect(ui->btn_personal, &QPushButton::clicked, this,&chatWidget::switchWin);
	
}

void chatWidget::switchWin()
{
	qDebug() << "send show";
	emit interviewShow();

}
