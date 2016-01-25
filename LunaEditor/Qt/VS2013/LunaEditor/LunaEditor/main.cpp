#include "lunaeditor.h"
#include <QtWidgets/QApplication>
#include <QtCore/QTextCodec>

int main(int argc, char *argv[])
{
	QTextCodec *codec = QTextCodec::codecForName("UTF-8");

	//QTextCodec::setCodecForTr(codec);
	
	
	QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
	//QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

	QApplication a(argc, argv);
	LunaEditor w;
	w.show();
	return a.exec();
}
