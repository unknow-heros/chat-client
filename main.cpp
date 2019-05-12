
#include <QtWidgets/QApplication>
#include "General\ReadFileContent.h"
#include "Master\MasterController.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	qApp->setStyleSheet(ReadFileContent::getFileContent("./qss/online.qss"));
	MasterController m(NULL);	
	return a.exec();
}
