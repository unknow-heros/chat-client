#ifndef CHATCENTER_H
#define CHATCENTER_H

#include <QTreeWidget>
#include <QStringList>

#include "person.h"



class chatCenter : public QTreeWidget
{
	Q_OBJECT

public:
	explicit chatCenter(QWidget *parent);
	~chatCenter();
public:
	void menuInit();													//初始化菜单
	void connectInit();													//初始化信号槽
	void mousePressEvent(QMouseEvent *event);							//鼠标按下事件
	void contextMenuEvent(QContextMenuEvent * event);					//菜单事件

	void friendListInit(QStringList friendList, int listNum);			//初始化好友列表

	void addfriend();													//测试
	void addFriend(person * per, int index);							//添加好友
	
	void delFriend(QTreeWidgetItem * item);								//删除好友

	void updateFriendName(QTreeWidgetItem * item, QString& uName);		//更新好友名称
	void updateFriendSign(QTreeWidgetItem * item, QString& sName);		//更新好友个性签名
	void updateFriendHead(QTreeWidgetItem * item, QString& headFile);	//更新好友头像

	void addMyFriendInfo(QTreeWidgetItem* pRootGroupItem);				//添加我的好友

public slots:
	void slotAddGroup();				//添加组
	void slotDelGroup();				//删除组
	void slotAddBuddy();				//添加好友
	void slotDelBuddy();				//删除好友
	void slotRename();					//重命名组
	void slotRenameEditFshed();			//命名完成


private:
	QMap<QTreeWidgetItem*, bool> m_isHideMap;				//用来判断该组是否隐藏了
	QMap<QTreeWidgetItem*, QTreeWidgetItem*> m_groupMap;	// 组容器 - key:项 value:组
	QTreeWidgetItem *currentItem = NULL;					//当前的项

	QMenu* m_blankMenu =  NULL;								//点击空白上的菜单
	QMenu* m_groupMenu =  NULL;								//点击组上单的菜单
	QMenu* m_personMenu = NULL;								//点击人上的菜单

	QAction* m_addGroup = NULL;								//添加好友
	QAction* m_delGroup = NULL;								//删除好友
	QAction* m_rename =   NULL;								//重命名
	QAction* m_addBuddy = NULL;								//添加好友
	QAction* m_delBuddy = NULL;								//删除好友

private:
	void onItemExpanded(QTreeWidgetItem * item);
	void onItemCollapsed(QTreeWidgetItem * item);
	void onItemClicked(QTreeWidgetItem * item, int column);

};

#endif // CHATCENTER_H
