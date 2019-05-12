#include "interviewWidget.h"
#include "ui_interviewWidget.h"

interviewWidget::interviewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::interviewWidget)
{
    ui->setupUi(this);
}

interviewWidget::~interviewWidget()
{
    delete ui;
}
