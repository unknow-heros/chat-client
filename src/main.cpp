
#include <QtWidgets/QApplication>
#include "Comment/ReadFileContent.h"
#include "Master\MasterController.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	qApp->setStyleSheet(ReadFileContent::getFileContent(":/qss/Resources/qss/online.css"));
	MasterController m(NULL);	
	return a.exec();
}
