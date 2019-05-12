#include "person.h"

person::person(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::person)
{
	ui->setupUi(this);
}

person::~person()
{
	delete ui;
}

void person::setUserName(const QString& uName)
{
	this->m_uName = uName;
	ui->label_hisName->setText(this->m_uName);
}

void person::setSignName(const QString& sName)
{
	this->m_sName = sName;
	ui->label_signature->setText(this->m_sName);
}

void person::setHeadImage(const QString & head)
{
	this->m_headFile = head;
	ui->btn_head->setIcon(QIcon(this->m_headFile));
	ui->btn_head->setIconSize(QSize(42, 42));
}

QString person::getUserName()
{
	return this->m_uName;
}
