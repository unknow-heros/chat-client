#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QAction>
#include <QIcon>
#include <QPainter>
#include <QMouseEvent>
#include <QSpacerItem>
#include <QProxyStyle>
#include <QTimer>
#include "Chat/person.h"
#include "Chat/chatWidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
	,ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
}

//右上角关闭按钮槽函数
void MainWindow::winClose()
{
    this->hide();
}

//信号与槽初始化
void MainWindow::initAction()
{
    connect(this,&MainWindow::destroyed,this,&MainWindow::winClose);							//右上角关闭按钮
}

//初始化UI
void MainWindow::initUI()
{
}

void MainWindow::setHeadImage(QString imagePath)
{
}

void MainWindow::onOpenPersonalCenter()
{
}

void MainWindow::onOpenChatWidget()
{
}
