#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QAction>
#include <QIcon>
#include <QPainter>
#include <QMouseEvent>
#include <QSpacerItem>
#include <QProxyStyle>
#include <QTimer>

#include "person.h"
#include "VideoVM/interviewWidget.h"
#include "chatCenter/chatWidget.h"
#include "PersonalCenter/personalcenter.h"
#include "ContactsCenter/contactscenter.h"

QWidget* MainWindow::m_currentWidget_ptr_ = nullptr;

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
	,ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->uiInit();
    this->connect_init();

}

MainWindow::~MainWindow()
{
	delete m_chat_widget_ptr_;
	delete m_contacts_center_ptr_;
	delete m_interview_ptr_;
	delete m_personal_center_ptr_;
	delete m_mid_sub_window_ptr_;
	delete m_mdiarea_ptr_;
	delete ui;
}

//右上角关闭按钮槽函数
void MainWindow::winClose()
{
    this->hide();
    emit this->proClose();
}

//信号与槽初始化
void MainWindow::connect_init()
{
    connect(this,&MainWindow::destroyed,this,&MainWindow::winClose);							//右上角关闭按钮
		
    connect(ui->btn_me,&QPushButton::clicked,this,&MainWindow::onOpenPersonalCenter);			//切换到个人中心
    connect(ui->btn_chart,&QPushButton::clicked,this,&MainWindow::onOpenChatWidget);			//切换到聊天页面
    connect(ui->btn_contacts,&QPushButton::clicked,this,&MainWindow::onOpenContactsCenter);		//切换到联系人
    connect(ui->btn_videoIVW,&QPushButton::clicked,this,&MainWindow::onOpenVideoVM);			//切换到视频面试页面
}

//初始化UI
void MainWindow::uiInit()
{
	m_mdiarea_ptr_ = new QMdiArea(this);
	ui->contentLayout->layout()->addWidget(m_mdiarea_ptr_);
	QHBoxLayout *layout = new QHBoxLayout;
	m_mdiarea_ptr_->setLayout(layout);

    this->m_personal_center_ptr_ = new PersonalCenter();
    this->m_chat_widget_ptr_ = new chatWidget(); 
	this->m_contacts_center_ptr_ = new ContactsCenter();

    if(this->m_interview_ptr_ == NULL) {
        this->m_interview_ptr_ = new interviewWidget;
    }

	setCurrentWidget(this->m_personal_center_ptr_);
}

void MainWindow::setHeadImage(QString imagePath)
{
    ui->btn_me->setIcon(QIcon(imagePath));
}

void MainWindow::setCurrentWidget(QWidget * wid)
{
	m_mdiarea_ptr_->removeSubWindow(this->m_currentWidget_ptr_);
	m_mdiarea_ptr_->closeActiveSubWindow();
	m_mid_sub_window_ptr_ = m_mdiarea_ptr_->addSubWindow(wid);
	m_mid_sub_window_ptr_->setWindowFlags(Qt::FramelessWindowHint);
	m_mid_sub_window_ptr_->showMaximized();
	wid->show();
	this->m_currentWidget_ptr_ = wid;
}

void MainWindow::onOpenPersonalCenter()
{
	setCurrentWidget(this->m_personal_center_ptr_);
}

void MainWindow::onOpenChatWidget()
{
	setCurrentWidget(this->m_chat_widget_ptr_);
}

void MainWindow::onOpenContactsCenter()
{
	setCurrentWidget(this->m_contacts_center_ptr_);
}

void MainWindow::onOpenVideoVM()
{
	setCurrentWidget(this->m_interview_ptr_);
}



