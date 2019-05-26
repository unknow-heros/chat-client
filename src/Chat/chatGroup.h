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
	void setText(const QString& title);			//��������
	void setExpanded(bool expand);				//�����Ƿ�����
	void setRotation(int rotation);				//������ת�Ƕ�
	void setFriendNum(int num);					//���ú�������
	void setFriendOnlineNum(int num);			//���ú�����������

	QString getText();

private:
	void paintEvent(QPaintEvent * event);		//��ͼ�¼�	
	int rotation();				

private:
	QPropertyAnimation * m_animation = NULL;	//����Ч��
	QString m_titleText;						//����
	int m_rotation = 0;							//��ת�Ƕ�
	int m_friendNum = 0;						//���Ѹ���
	int m_freendOnlineNum = 0;					//������������
};

#endif // CHATGROUP_H
