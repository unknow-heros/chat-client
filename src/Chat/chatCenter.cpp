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

	this->setExpandsOnDoubleClick(false);	//�ر�˫��չ��
	this->header()->setVisible(false);		//�رձ���

	QStringList testList;
	testList.append(QString::fromLocal8Bit("�ҵĺ���"));
	testList.append(QString::fromLocal8Bit("�ҵ�ͬ��"));
	testList.append(QString::fromLocal8Bit("��������"));
	testList.append(QString::fromLocal8Bit("İ����"));
	testList.append(QString::fromLocal8Bit("������"));

	this->setIndentation(0);
	this->friendListInit(testList, 5);
	//this->addfriend();
	
	//����1
	person* pContactItem = new person(this);
	pContactItem->setHeadImage(":/icon/Resources/images/head2.jpg");
	pContactItem->setUserName(QString::fromLocal8Bit("����122"));
	pContactItem->setSignName(QString::fromLocal8Bit("����221"));
	this->addFriend(pContactItem, 0);


	//this->topLevelItem(0)->addChild(new QTreeWidgetItem({ "fdsafdaf") });
	
	//���º���
	//this->updateFriend(this->topLevelItem(0)->child(1));
	this->updateFriendName(this->topLevelItem(0)->child(3),QString("oooooo"));

	//ɾ������
	//this->delFriend(this->topLevelItem(1)->child(1));

	this->menuInit();		//�һ��˵���ʼ��
	this->initAction();	//�źŲ۳�ʼ��	
	this->setFocusPolicy(Qt::NoFocus);							//ȥ��itemѡ��ʱ�����߱߿�
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);	//ˮƽ�������ر�

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

	this->m_addGroup = new QAction(QString::fromLocal8Bit("��ӷ���"), this);
	this->m_delGroup = new QAction(QString::fromLocal8Bit("ɾ������"), this);
	this->m_rename   = new QAction(QString::fromLocal8Bit("������"),   this);
	this->m_addBuddy = new QAction(QString::fromLocal8Bit("��Ӻ���"), this);
	this->m_delBuddy = new QAction(QString::fromLocal8Bit("ɾ������"), this);

	//����հ״�
	this->m_blankMenu->addAction(m_addGroup);
	
	//������ϵĲ˵�
	this->m_groupMenu->addAction(m_addGroup);
	this->m_groupMenu->addAction(m_rename);
	this->m_groupMenu->addAction(m_delGroup);

	//����������ϵĲ˵�
	this->m_personMenu->addAction(m_delBuddy);

}

//�źŲ۳�ʼ��
void chatCenter::initAction()
{
	connect(m_addGroup, &QAction::triggered, this, &chatCenter::slotAddGroup);	//�����
	connect(m_delGroup, &QAction::triggered, this, &chatCenter::slotDelGroup);	//ɾ����
	connect(m_rename,   &QAction::triggered, this, &chatCenter::slotRename  );	//��������
	connect(m_addBuddy, &QAction::triggered, this, &chatCenter::slotAddBuddy);	//��Ӻ���
	connect(m_delBuddy, &QAction::triggered, this, &chatCenter::slotDelBuddy);	//ɾ������

	connect(this, &QTreeWidget::itemClicked, this, &chatCenter::slotClickFriend);  //�������
}

void chatCenter::mousePressEvent(QMouseEvent *event)
{	
	// ��������û���mousePressEvent��item��select����첻��Ӧ,���ø��࣬
	//��QSS��Ч����ΪQSS���ڸ���QListWidget����������Ӵ��ڣ��������ϲ㴰��
	//�Ǹ����ڸ������ϵģ��������ڸ����ڲ�����Ϣ
	QTreeWidget::mousePressEvent(event);




	//��ȡ���λ�õ�Item
	currentItem = this->itemAt(mapFromGlobal(QCursor::pos()));

	//����������������ǵ��������
	if ( event->button() == Qt::LeftButton && currentItem != NULL && currentItem == this->m_groupMap.value(currentItem))
	{
		if (this->m_isHideMap.value(currentItem))  //�������ǰ�����أ�����ʾ
		{
			//������Ķ�Ӧ�����������ͺ��ѣ�
			foreach(QTreeWidgetItem* subItem, m_groupMap.keys(currentItem))
			if (subItem != currentItem)
			{
				subItem->setHidden(false);				//����ȫ����ʾ
			}
			this->m_isHideMap.insert(currentItem, false);	//��������Ϊ��ʾ״̬
			qDebug() << "zhangkai";
			currentItem->setExpanded(true);
			chatGroup * tmp = dynamic_cast<chatGroup*>(this->itemWidget(currentItem, 0));
			tmp->setRotation(90);
		}
		else                         //������ǰ����ʾ����Ӱ��
		{
			//������Ķ�Ӧ�����������ͺ��ѣ�
			foreach(QTreeWidgetItem* subItem, m_groupMap.keys(currentItem))
			if (subItem != currentItem)
			{
				subItem->setHidden(true);				//����ȫ����ʾ
			}
			this->m_isHideMap.insert(currentItem, true);            //���ø���Ϊ����״̬
			qDebug() << "yingcang";
			currentItem->setExpanded(false);
			chatGroup * tmp = dynamic_cast<chatGroup*>(this->itemWidget(currentItem, 0));
			tmp->setRotation(0);
		}	 
	}
}

//˫���¼�
void chatCenter::mouseDoubleClickEvent(QMouseEvent*event)
{

	// ��������û���mousePressEvent��item��select����첻��Ӧ,���ø��࣬
	//��QSS��Ч����ΪQSS���ڸ���QListWidget����������Ӵ��ڣ��������ϲ㴰��
	//�Ǹ����ڸ������ϵģ��������ڸ����ڲ�����Ϣ
	QTreeWidget::mouseDoubleClickEvent(event);
	//��ȡ���λ�õ�Item
	currentItem = this->itemAt(mapFromGlobal(QCursor::pos()));

	//���˫��������� �����ǵ�����Ǻ���
	if (event->button() == Qt::LeftButton && currentItem != NULL && currentItem != this->m_groupMap.value(currentItem))
	{
		person * tmp = dynamic_cast<person*>(this->itemWidget(currentItem, 0));
		qDebug() << tmp->getUserName();
	}
}




//�˵��¼�
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
		this->m_isHideMap.insert(pRootFriendItem, true);				//Ĭ�ϸ���Ϊ����״̬

		//����Data�������֣�Item�Ƿ���ڵ㻹���ӽڵ㣬0�������ڵ㣬1�����ӽڵ�
		pRootFriendItem->setData(0, Qt::UserRole, 0);

		chatGroup *pItemName = new chatGroup(this);
		QString qsGroupName = QString::fromLocal8Bit("%1").arg(friendList.at(i));
		pItemName->setText(qsGroupName);
		pItemName->setFriendNum(5);
		pItemName->setFriendOnlineNum(1);


		this->addTopLevelItem(pRootFriendItem);
		this->setItemWidget(pRootFriendItem, 0, pItemName);

		this->setAnimated(false);      //���ö���չ��
		for (int m = 0; m < 5; ++m)
		{
			this->addMyFriendInfo(pRootFriendItem);
		}
	}
}

//��Ӻ���
void chatCenter::addfriend()
{
	QTreeWidgetItem *pChild = new QTreeWidgetItem();
	person* pContactItem = new person(this);
	pContactItem->setHeadImage(":/icon/Resources/images/head2.jpg");
	pContactItem->setUserName(QString::fromLocal8Bit("����"));
	pContactItem->setSignName(QString::fromLocal8Bit("����"));

	this->topLevelItem(1)->addChild(pChild);
	this->setItemWidget(pChild, 0, pContactItem);
}

//��Ӻ���
void chatCenter::addFriend(person * per,int index)
{
	QTreeWidgetItem *pChild = new QTreeWidgetItem();
	this->topLevelItem(index)->addChild(pChild);
	this->setItemWidget(pChild, 0, per);
}

//ɾ������
void chatCenter::delFriend(QTreeWidgetItem * item)
{
	person * per = dynamic_cast<person*>(this->itemWidget(item, 0));
	this->removeItemWidget(item,0);
	delete per;
	delete item;
}

//���º�������
void chatCenter::updateFriendName(QTreeWidgetItem * item, QString& uName)
{
	person * per = dynamic_cast<person*>(this->itemWidget(item, 0));
	per->setUserName(uName);
}

//���º��Ѹ���ǩ��
void chatCenter::updateFriendSign(QTreeWidgetItem * item, QString& sName)
{
	person * per = dynamic_cast<person*>(this->itemWidget(item, 0));
	per->setUserName(sName);
}

//���º���ͷ��
void chatCenter::updateFriendHead(QTreeWidgetItem * item, QString&headFile)
{
	person * per = dynamic_cast<person*>(this->itemWidget(item, 0));
	per->setHeadImage(headFile);
}


void chatCenter::addMyFriendInfo(QTreeWidgetItem* pRootGroupItem)
{
	QTreeWidgetItem *pChild = new QTreeWidgetItem();
	//����ӽڵ�
	pChild->setData(0, Qt::UserRole, 1);
	person* pContactItem = new person(this);
	pContactItem->setHeadImage(":/icon/Resources/images/head1.jpg");
	pContactItem->setUserName(QString::fromLocal8Bit("HFY"));
	pContactItem->setSignName(QString::fromLocal8Bit("��ӭ����HFY"));
	pRootGroupItem->addChild(pChild);

	this->setItemWidget(pChild, 0, pContactItem);
	
}

//�����
void chatCenter::slotAddGroup()
{
	QTreeWidgetItem *pRootFriendItem = new QTreeWidgetItem();
	pRootFriendItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);

	this->m_groupMap.insert(pRootFriendItem, pRootFriendItem);
	this->m_isHideMap.insert(pRootFriendItem, true);				//Ĭ�ϸ���Ϊ����״̬

																	//����Data�������֣�Item�Ƿ���ڵ㻹���ӽڵ㣬0�������ڵ㣬1�����ӽڵ�
	//pRootFriendItem->setData(0, Qt::UserRole, 0);

	chatGroup *pItemName = new chatGroup(this);
	QString qsGroupName = QString::fromLocal8Bit("%1").arg(QString::fromLocal8Bit("δ����"));
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
