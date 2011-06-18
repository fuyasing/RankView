#include <QtGui/QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QTranslator qtTranslator;
	qtTranslator.load("qt_" + QLocale::system().name(),
			QLibraryInfo::location(QLibraryInfo::TranslationsPath));
	app.installTranslator(&qtTranslator);

	QTranslator appTranslator;
	appTranslator.load("rankview_" + QLocale::system().name());
	//appTranslator.load("rankview_" + QLocale::system().name(), QDir::currentPath()+"/i18n");
	app.installTranslator(&appTranslator);

	MainWindow w;
	w.show();

	return app.exec();
}
