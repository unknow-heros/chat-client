#include "ReadFileContent.h"
#include <QFile>

ReadFileContent::ReadFileContent()
{
}

ReadFileContent::~ReadFileContent()
{
}

QString ReadFileContent::getFileContent(const QString filePath)
{
    if(nullptr == filePath)
        return "";

    QString content;
	QFile file(filePath);
	file.open(QFile::ReadOnly);
	if (file.isOpen())
	{
		content = QLatin1String(file.readAll());
        file.close();
    }
    return content;
}
