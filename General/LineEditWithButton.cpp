#include "LineEditWithButton.h"

LineEditWithButton::LineEditWithButton(QWidget *parent)
	: CompleteLineEdit(parent)
{

}

LineEditWithButton::~LineEditWithButton()
{

}

void LineEditWithButton::setButtonImage(QString icon)
{
	this->m_button->setFlat(true);
	this->m_button->setText("");
	if (!icon.isEmpty())
	{
		this->m_button->setIcon(QIcon(icon));
	}
}

void LineEditWithButton::resizeEvent(QResizeEvent* e)
{

}

void LineEditWithButton::enterEvent(QEvent* e)
{

}

bool LineEditWithButton::eventFilter(QObject* o, QEvent* e)
{
	return true;
}

void LineEditWithButton::leaveEvent(QEvent* e)
{

}
