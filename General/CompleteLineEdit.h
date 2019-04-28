
#ifndef COMPLETELINEEDIT_H
#define COMPLETELINEEDIT_H

#include <QLineEdit>
#include <QStringList>

class QListView;
class QStringListModel;
class QModelIndex;

class CompleteLineEdit : public QLineEdit
{
	Q_OBJECT

public:
	CompleteLineEdit(QWidget *parent);
	~CompleteLineEdit();
public:
	void setCompleteStringList(const QStringList& words);

public slots:
	void setCompleter(const QString &text);
	void completeText(const QModelIndex &index);
	void setMaxMatchCount(int count);



protected:
	virtual void keyPressEvent(QKeyEvent *e);

signals:
	void focusOut();

private:
	QStringList m_words;	
	QListView *m_listView;
	QStringListModel *m_model;
	int m_maxMatchMount;
	
	
};

#endif // COMPLETELINEEDIT_H
