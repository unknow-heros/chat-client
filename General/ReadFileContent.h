#ifndef READFILECONTENT_GENERAL_H_
#define READFILECONTENT_GENERAL_H_

#include <QString>

class ReadFileContent
{
private:
	ReadFileContent();
	~ReadFileContent();

public:
	static QString getFileContent(QString filePath);

private:
};

#endif // !READFILECONTENT_GENERAL_H_

