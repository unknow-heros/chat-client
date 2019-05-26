#include "CompleteLineEdit.h"

#include <QKeyEvent>
#include <QListView>
#include <QStringListModel>
#include <QDebug>


CompleteLineEdit::CompleteLineEdit(QWidget *parent)
	: QLineEdit(parent)
{
	m_listView = new QListView(this);
	m_model = new QStringListModel(this);
	m_listView->setAttribute(Qt::WA_StaticContents);
	m_listView->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);
	m_listView->setFocusPolicy(Qt::NoFocus);
	m_listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_listView->setFocusProxy(this);
	m_listView->hide();

	connect(this, &QLineEdit::textChanged, this, &CompleteLineEdit::setCompleter);
	connect(m_listView, &QListView::clicked, this, &CompleteLineEdit::completeText);
	connect(this, &CompleteLineEdit::focusOut, this, &QLineEdit::close, Qt::QueuedConnection);
}

CompleteLineEdit::~CompleteLineEdit()
{

}


void CompleteLineEdit::setCompleteStringList(const QStringList& words)
{
	this->m_words = words;
}

void CompleteLineEdit::setCompleter(const QString &text)
{
	if (text.isEmpty())
	{
		m_listView->hide();
		return;
	}

	if (!this->hasFocus())
		return;

	if ((text.length() > 1) && (!m_listView->isHidden()))
	{
		return;
	}

	QStringList sl;
	for (QString& word : m_words)
	{
		if (word.contains(text, Qt::CaseInsensitive))
		{
			sl << word;
			if (sl.size() >= m_maxMatchMount)
				break;
		}
	}

	m_model->setStringList(sl);
	m_listView->setModel(m_model);

	if (m_model->rowCount() == 0)
	{
		return;
	}

	// Position the text edit
	m_listView->setMinimumWidth(width());
	m_listView->setMaximumWidth(width());

	QPoint p(0, height());
	int x = mapToGlobal(p).x();
	int y = mapToGlobal(p).y() + 1;

	m_listView->move(x, y);
	m_listView->show();
}

void CompleteLineEdit::completeText(const QModelIndex &index)
{
	QString text = index.data().toString();
	setText(text);
	emit editingFinished();
	m_listView->hide();
}

void CompleteLineEdit::setMaxMatchCount(int count)
{
	this->m_maxMatchMount = count;
}

void CompleteLineEdit::keyPressEvent(QKeyEvent *e)
{
	if (!m_listView->isHidden())
	{
		int key = e->key();
		int count = m_listView->model()->rowCount();
		QModelIndex currentIndex = m_listView->currentIndex();

		if (Qt::Key_Down == key)
		{

			int row = currentIndex.row() + 1;
			if (row >= count)
			{
				row = 0;
			}

			QModelIndex index = m_listView->model()->index(row, 0);
			m_listView->setCurrentIndex(index);
		}
		else if (Qt::Key_Up == key)
		{

			int row = currentIndex.row() - 1;
			if (row < 0)
			{
				row = count - 1;
			}

			QModelIndex index = m_listView->model()->index(row, 0);
			m_listView->setCurrentIndex(index);
		}
		else if (Qt::Key_Escape == key)
		{

			m_listView->hide();
		}
		else if (Qt::Key_Enter == key || Qt::Key_Return == key)
		{
			if (currentIndex.isValid())
			{
				QString text = m_listView->currentIndex().data().toString();
				setText(text);
				emit editingFinished();
			}

			m_listView->hide();
		}
		else
		{
			m_listView->hide();
			QLineEdit::keyPressEvent(e);
		}
	}
	else
	{
		QLineEdit::keyPressEvent(e);
	}
}
