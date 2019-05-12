#include "chatCenter.h"
#include "chatGroup.h"

#include <QMenu>
#include <QString>
#include <QStringList>
#include <QMouseEvent>

#include <QDebug>
#include <qheaderview.h>


chatCenter::chatCenter(QWidget *parent)
	: QTreeWidget(parent)
{

	this->setExpandsOnDoubleClick(false);	//关闭双击展开
	this->header()->setVisible(false);		//关闭标题

	QStringList testList;
	testList.append(QString::fromLocal8Bit("我的好友"));
	testList.append(QString::fromLocal8Bit("我的同事"));
	testList.append(QString::fromLocal8Bit("隔壁老王"));
	testList.append(QString::fromLocal8Bit("陌生人"));
	testList.append(QString::fromLocal8Bit("黑名单"));

	this->setIndentation(0);
	this->friendListInit(testList, 5);
	//this->addfriend();
	
	//测试1
	person* pContactItem = new person(this);
	pContactItem->setHeadImage(":/icon/Resources/images/head2.jpg");
	pContactItem->setUserName(QString::fromLocal8Bit("测试122"));
	pContactItem->setSignName(QString::fromLocal8Bit("测试221"));
	this->addFriend(pContactItem, 0);


	//this->topLevelItem(0)->addChild(new QTreeWidgetItem({ "fdsafdaf") });
	
	//更新好友
	//this->updateFriend(this->topLevelItem(0)->child(1));
	this->updateFriendName(this->topLevelItem(0)->child(3),QString("oooooo"));

	//删除好友
	//this->delFriend(this->topLevelItem(1)->child(1));

	this->menuInit();		//右击菜单初始化
	this->connectInit();	//信号槽初始化	
	this->setFocusPolicy(Qt::NoFocus);							//去除item选中时的虚线边框
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);	//水平滚动条关闭

}

chatCenter::~chatCenter()
{
	delete this->m_blankMenu;
	delete this->m_groupMenu;
	delete this->m_personMenu;
}

void chatCenter::menuInit()
{
	this->m_blankMenu = new QMenu();
	this->m_groupMenu = new QMenu();
	this->m_personMenu = new QMenu();

	this->m_addGroup = new QAction(QString::fromLocal8Bit("添加分组"), this);
	this->m_delGroup = new QAction(QString::fromLocal8Bit("删除该组"), this);
	this->m_rename   = new QAction(QString::fromLocal8Bit("重命名"),   this);
	this->m_addBuddy = new QAction(QString::fromLocal8Bit("添加好友"), this);
	this->m_delBuddy = new QAction(QString::fromLocal8Bit("删除好友"), this);

	//点击空白处
	this->m_blankMenu->addAction(m_addGroup);
	
	//点击组上的菜单
	this->m_groupMenu->addAction(m_addGroup);
	this->m_groupMenu->addAction(m_rename);
	this->m_groupMenu->addAction(m_delGroup);

	//点击到好友上的菜单
	this->m_personMenu->addAction(m_delBuddy);

}

//信号槽初始化
void chatCenter::connectInit()
{
	connect(m_addGroup, &QAction::triggered, this, &chatCenter::slotAddGroup);	//添加组
	connect(m_delGroup, &QAction::triggered, this, &chatCenter::slotDelGroup);	//删除组
	connect(m_rename,   &QAction::triggered, this, &chatCenter::slotRename  );	//重命名组
	connect(m_addBuddy, &QAction::triggered, this, &chatCenter::slotAddBuddy);	//添加好友
	connect(m_delBuddy, &QAction::triggered, this, &chatCenter::slotDelBuddy);	//删除好友

	connect(this, &QTreeWidget::itemClicked, this, &chatCenter::slotClickFriend);  //点击好友
}

void chatCenter::mousePressEvent(QMouseEvent *event)
{	
	// 如果不调用基类mousePressEvent，item被select会半天不响应,调用父类，
	//让QSS起效，因为QSS基于父类QListWidget，子类就是子窗口，就是最上层窗口
	//是覆盖在父窗口上的，所以先于父窗口捕获消息
	QTreeWidget::mousePressEvent(event);




	//获取鼠标位置的Item
	currentItem = this->itemAt(mapFromGlobal(QCursor::pos()));

	//如果点击的左键并且是点击的是组
	if ( event->button() == Qt::LeftButton && currentItem != NULL && currentItem == this->m_groupMap.value(currentItem))
	{
		if (this->m_isHideMap.value(currentItem))  //如果是先前是隐藏，则显示
		{
			//遍历组的对应的项（包括自身和好友）
			foreach(QTreeWidgetItem* subItem, m_groupMap.keys(currentItem))
			if (subItem != currentItem)
			{
				subItem->setHidden(false);				//好友全部显示
			}
			this->m_isHideMap.insert(currentItem, false);	//该组设置为显示状态
			qDebug() << "zhangkai";
			currentItem->setExpanded(true);
			chatGroup * tmp = dynamic_cast<chatGroup*>(this->itemWidget(currentItem, 0));
			tmp->setRotation(90);
		}
		else                         //否则，先前是显示，则影藏
		{
			//遍历组的对应的项（包括自身和好友）
			foreach(QTreeWidgetItem* subItem, m_groupMap.keys(currentItem))
			if (subItem != currentItem)
			{
				subItem->setHidden(true);				//好友全部显示
			}
			this->m_isHideMap.insert(currentItem, true);            //设置该组为隐藏状态
			qDebug() << "yingcang";
			currentItem->setExpanded(false);
			chatGroup * tmp = dynamic_cast<chatGroup*>(this->itemWidget(currentItem, 0));
			tmp->setRotation(0);
		}	 
	}
}

//双击事件
void chatCenter::mouseDoubleClickEvent(QMouseEvent*event)
{

	// 如果不调用基类mousePressEvent，item被select会半天不响应,调用父类，
	//让QSS起效，因为QSS基于父类QListWidget，子类就是子窗口，就是最上层窗口
	//是覆盖在父窗口上的，所以先于父窗口捕获消息
	QTreeWidget::mouseDoubleClickEvent(event);
	//获取鼠标位置的Item
	currentItem = this->itemAt(mapFromGlobal(QCursor::pos()));

	//如果双击击的左键 并且是点击的是好友
	if (event->button() == Qt::LeftButton && currentItem != NULL && currentItem != this->m_groupMap.value(currentItem))
	{
		person * tmp = dynamic_cast<person*>(this->itemWidget(currentItem, 0));
		qDebug() << tmp->getUserName();
	}
}




//菜单事件
void chatCenter::contextMenuEvent(QContextMenuEvent * event)
{
	QTreeWidget::contextMenuEvent(event);
	if (currentItem == NULL)
	{
		this->m_blankMenu->exec(QCursor::pos());
		return;
	}

	if (currentItem == m_groupMap.value(currentItem))
	{
		this->m_groupMenu->exec(QCursor::pos());
	}
	else
	{
		this->m_personMenu->exec(QCursor::pos());
	}
}

void chatCenter::friendListInit(QStringList friendList, int listNum)
{
	for (int i =0 ; i < friendList.size(); ++i)
	{
		QTreeWidgetItem *pRootFriendItem = new QTreeWidgetItem();
		pRootFriendItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);

		this->m_groupMap.insert(pRootFriendItem, pRootFriendItem);
		this->m_isHideMap.insert(pRootFriendItem, true);				//默认该组为隐藏状态

		//设置Data用于区分，Item是分组节点还是子节点，0代表分组节点，1代表子节点
		pRootFriendItem->setData(0, Qt::UserRole, 0);

		chatGroup *pItemName = new chatGroup(this);
		QString qsGroupName = QString::fromLocal8Bit("%1").arg(friendList.at(i));
		pItemName->setText(qsGroupName);
		pItemName->setFriendNum(5);
		pItemName->setFriendOnlineNum(1);


		this->addTopLevelItem(pRootFriendItem);
		this->setItemWidget(pRootFriendItem, 0, pItemName);

		this->setAnimated(false);      //设置动画展开
		for (int m = 0; m < 5; ++m)
		{
			this->addMyFriendInfo(pRootFriendItem);
		}
	}
}

//添加好友
void chatCenter::addfriend()
{
	QTreeWidgetItem *pChild = new QTreeWidgetItem();
	person* pContactItem = new person(this);
	pContactItem->setHeadImage(":/icon/Resources/images/head2.jpg");
	pContactItem->setUserName(QString::fromLocal8Bit("测试"));
	pContactItem->setSignName(QString::fromLocal8Bit("测试"));

	this->topLevelItem(1)->addChild(pChild);
	this->setItemWidget(pChild, 0, pContactItem);
}

//添加好友
void chatCenter::addFriend(person * per,int index)
{
	QTreeWidgetItem *pChild = new QTreeWidgetItem();
	this->topLevelItem(index)->addChild(pChild);
	this->setItemWidget(pChild, 0, per);
}

//删除好友
void chatCenter::delFriend(QTreeWidgetItem * item)
{
	person * per = dynamic_cast<person*>(this->itemWidget(item, 0));
	this->removeItemWidget(item,0);
	delete per;
	delete item;
}

//更新好友名称
void chatCenter::updateFriendName(QTreeWidgetItem * item, QString& uName)
{
	person * per = dynamic_cast<person*>(this->itemWidget(item, 0));
	per->setUserName(uName);
}

//更新好友个性签名
void chatCenter::updateFriendSign(QTreeWidgetItem * item, QString& sName)
{
	person * per = dynamic_cast<person*>(this->itemWidget(item, 0));
	per->setUserName(sName);
}

//更新好友头像
void chatCenter::updateFriendHead(QTreeWidgetItem * item, QString&headFile)
{
	person * per = dynamic_cast<person*>(this->itemWidget(item, 0));
	per->setHeadImage(headFile);
}


void chatCenter::addMyFriendInfo(QTreeWidgetItem* pRootGroupItem)
{
	QTreeWidgetItem *pChild = new QTreeWidgetItem();
	//添加子节点
	pChild->setData(0, Qt::UserRole, 1);
	person* pContactItem = new person(this);
	pContactItem->setHeadImage(":/icon/Resources/images/head1.jpg");
	pContactItem->setUserName(QString::fromLocal8Bit("HFY"));
	pContactItem->setSignName(QString::fromLocal8Bit("欢迎访问HFY"));
	pRootGroupItem->addChild(pChild);

	this->setItemWidget(pChild, 0, pContactItem);
	
}

//添加组
void chatCenter::slotAddGroup()
{
	QTreeWidgetItem *pRootFriendItem = new QTreeWidgetItem();
	pRootFriendItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);

	this->m_groupMap.insert(pRootFriendItem, pRootFriendItem);
	this->m_isHideMap.insert(pRootFriendItem, true);				//默认该组为隐藏状态

																	//设置Data用于区分，Item是分组节点还是子节点，0代表分组节点，1代表子节点
	//pRootFriendItem->setData(0, Qt::UserRole, 0);

	chatGroup *pItemName = new chatGroup(this);
	QString qsGroupName = QString::fromLocal8Bit("%1").arg(QString::fromLocal8Bit("未命名"));
	pItemName->setText(qsGroupName);
	pItemName->setFriendNum(0);
	pItemName->setFriendOnlineNum(0);


	this->addTopLevelItem(pRootFriendItem);
	this->setItemWidget(pRootFriendItem, 0, pItemName);
}

void chatCenter::slotDelGroup()
{

}

void chatCenter::slotAddBuddy()
{

}

void chatCenter::slotDelBuddy()
{

}

void chatCenter::slotRename()
{

}

void chatCenter::slotRenameEditFshed()
{

}

void chatCenter::slotClickFriend(QTreeWidgetItem* item, int num)
{
	
	if (item == m_groupMap[item])
	{
		chatGroup * tmp = dynamic_cast<chatGroup*>(this->itemWidget(currentItem, 0));
		qDebug() << tmp->getText();
		//tmp->setText("llll");
	}
	else {
		person *p = dynamic_cast<person*>(this->itemWidget(item, 0));
		qDebug() << p->getUserName();
		//p->setUserName("ahah");
	}	
}

void chatCenter::onItemExpanded(QTreeWidgetItem * item)
{
	bool bIsChild = item->data(0, Qt::UserRole).toBool();
	if (!bIsChild)
	{
		chatGroup *prootItem = dynamic_cast<chatGroup*>(this->itemWidget(item, 0));
		if (prootItem)
		{
			prootItem->setExpanded(true);
		}
	}
}

void chatCenter::onItemCollapsed(QTreeWidgetItem * item)
{
	bool bIsChild = item->data(0, Qt::UserRole).toBool();
	if (!bIsChild)
	{
		chatGroup *prootItem = dynamic_cast<chatGroup*>(this->itemWidget(item, 0));
		if (prootItem)
		{
			prootItem->setExpanded(false);
		}
	}
}

void chatCenter::onItemClicked(QTreeWidgetItem * item, int column)
{
	bool bIsChild = item->data(0, Qt::UserRole).toBool();
	if (!bIsChild)
	{
		item->setExpanded(!item->isExpanded());
	}
}
