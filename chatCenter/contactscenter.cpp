#include "contactscenter.h"
#include "ui_contactscenter.h"

ContactsCenter::ContactsCenter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContactsCenter)
{
    ui->setupUi(this);
}

ContactsCenter::~ContactsCenter()
{
    delete ui;
}
