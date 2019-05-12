#ifndef CHATGROUP_H
#define CHATGROUP_H

#include <QLabel>

class QPropertyAnimation;

class chatGroup : public QLabel
{
	Q_OBJECT

public:
	chatGroup(QWidget *parent);
	~chatGroup();

public:
	void setText(const QString& title);			//设置组名
	void setExpanded(bool expand);				//设置是否隐藏
	void setRotation(int rotation);				//设置旋转角度
	void setFriendNum(int num);					//设置好友数量
	void setFriendOnlineNum(int num);			//设置好友在线数量

	QString getText();

private:
	void paintEvent(QPaintEvent * event);		//绘图事件	
	int rotation();				

private:
	QPropertyAnimation * m_animation = NULL;	//动画效果
	QString m_titleText;						//组名
	int m_rotation = 0;							//旋转角度
	int m_friendNum = 0;						//好友个数
	int m_freendOnlineNum = 0;					//好友在线人数
};

#endif // CHATGROUP_H
