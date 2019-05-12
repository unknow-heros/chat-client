#ifndef CHATCENTER_H
#define CHATCENTER_H

#include <QTreeWidget>
#include <QStringList>

#include "person.h"

#include <QVector>
class chatGroup;



class chatCenter : public QTreeWidget
{
	Q_OBJECT

public:
	explicit chatCenter(QWidget *parent = nullptr); 
	~chatCenter();
public:
	void menuInit();													//��ʼ���˵�
	void connectInit();													//��ʼ���źŲ�
	void mousePressEvent(QMouseEvent *event);							//��갴���¼�
	void mouseDoubleClickEvent(QMouseEvent*event);							//���˫���¼�
	void contextMenuEvent(QContextMenuEvent * event);					//�˵��¼�

	void friendListInit(QStringList friendList, int listNum);			//��ʼ�������б�

	void addfriend();													//����
	void addFriend(person * per, int index);							//��Ӻ���
	
	void delFriend(QTreeWidgetItem * item);								//ɾ������

	void updateFriendName(QTreeWidgetItem * item, QString& uName);		//���º�������
	void updateFriendSign(QTreeWidgetItem * item, QString& sName);		//���º��Ѹ���ǩ��
	void updateFriendHead(QTreeWidgetItem * item, QString& headFile);	//���º���ͷ��

	void addMyFriendInfo(QTreeWidgetItem* pRootGroupItem);				//����ҵĺ���

public slots:
	void slotAddGroup();				//�����
	void slotDelGroup();				//ɾ����
	void slotAddBuddy();				//��Ӻ���
	void slotDelBuddy();				//ɾ������
	void slotRename();					//��������
	void slotRenameEditFshed();			//�������

	void slotClickFriend(QTreeWidgetItem*, int);		//�������


private:
	QMap<QTreeWidgetItem*, bool> m_isHideMap;				//�����жϸ����Ƿ�������
	QMap<QTreeWidgetItem*, QTreeWidgetItem*> m_groupMap;	// ������ - key:�� value:��
	QTreeWidgetItem *currentItem = NULL;					//��ǰ����

	QMenu* m_blankMenu =  NULL;								//����հ��ϵĲ˵�
	QMenu* m_groupMenu =  NULL;								//������ϵ��Ĳ˵�
	QMenu* m_personMenu = NULL;								//������ϵĲ˵�

	QAction* m_addGroup = NULL;								//��Ӻ���
	QAction* m_delGroup = NULL;								//ɾ������
	QAction* m_rename =   NULL;								//������
	QAction* m_addBuddy = NULL;								//��Ӻ���
	QAction* m_delBuddy = NULL;								//ɾ������

private:
	void onItemExpanded(QTreeWidgetItem * item);
	void onItemCollapsed(QTreeWidgetItem * item);
	void onItemClicked(QTreeWidgetItem * item, int column);

	 QMap< chatGroup* ,QList<person*>> m_listFriend;
	

signals:
	

};

#endif // CHATCENTER_H
