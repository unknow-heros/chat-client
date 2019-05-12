#include "chatGroup.h"

#include <QPainter>
#include <QPropertyAnimation>

chatGroup::chatGroup(QWidget *parent)
	: QLabel(parent)
{
	this->setFixedHeight(32);
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

	//���ö���Ч��(������ ��Ҫ����)
// 	this->m_animation = new QPropertyAnimation(this, "rotation");
// 	m_animation->setDuration(50);
// 	m_animation->setEasingCurve(QEasingCurve::InQuad);
}

chatGroup::~chatGroup()
{
	delete this->m_animation;
}

//���ñ���
void chatGroup::setText(const QString& title)
{
	this->m_titleText = title;
	update();
}



//���ö���Ч��(������  )
void chatGroup::setExpanded(bool expand)
{
	if (expand == true)
	{
		this->m_animation->setEndValue(90);
	}
	else
	{
		this->m_animation->setEndValue(0);
	}
	//this->m_animation->start();
}

void chatGroup::paintEvent(QPaintEvent * event)
{
	QPainter painter(this);
	{
		painter.setRenderHint(QPainter::TextAntialiasing, true);
		QFont font;
		font.setPointSize(10);
		painter.setFont(font);
		QString tmp = QString::fromLocal8Bit("%1 %2/%3").arg(this->m_titleText).arg(this->m_freendOnlineNum).arg(this->m_friendNum);
		painter.drawText(24, 0, width() - 24, height(), Qt::AlignLeft | Qt::AlignVCenter, tmp);
	}

	{
		painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
		painter.save();
		//����ͼ
		QPixmap pixmap(":/chat/Resources/chat/0.png");
		QPixmap tmpPixmap(pixmap.size());
		tmpPixmap.fill(Qt::transparent);

		QPainter p(&tmpPixmap);
		p.setRenderHint(QPainter::SmoothPixmapTransform, true);

		//��תm_rotation�Ƕ�
		p.translate(pixmap.width() / 2, pixmap.height() / 2);
		p.rotate(m_rotation);
		p.drawPixmap(0 - pixmap.width() / 2, 0 - pixmap.height() / 2, pixmap);
		painter.drawPixmap(6, (height() - pixmap.height()) / 2, tmpPixmap);
		painter.restore();
	}

	__super::paintEvent(event);
}

//������ת�Ƕ�
void chatGroup::setRotation(int rotation)
{
	this->m_rotation = rotation;
	update();
}

//���ú�������
void chatGroup::setFriendNum(int num)
{
	this->m_friendNum = num;
	update();
}

//���ú�����������
void chatGroup::setFriendOnlineNum(int num)
{
	this->m_freendOnlineNum = num;
	update();
}

QString chatGroup::getText()
{
	return this->m_titleText;
}

int chatGroup::rotation()
{
	return this->m_rotation;
}
