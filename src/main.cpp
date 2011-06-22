#include <QtGui/QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include <QString>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QTranslator qtTranslator;
	qtTranslator.load("qt_" + QLocale::system().name(),
			QLibraryInfo::location(QLibraryInfo::TranslationsPath));
	app.installTranslator(&qtTranslator);

#ifdef Q_OS_MAC
	QString qmPath = QApplication::applicationDirPath();
#else 
#ifdef Q_OS_WIN32
	QString qmPath = QApplication::applicationDirPath();
#else
	QString qmPath = QApplication::applicationDirPath();
#endif
#endif
	QTranslator appTranslator;
	appTranslator.load("rankview_" + QLocale::system().name(),
			qmPath);
	app.installTranslator(&appTranslator);

	MainWindow w;
	w.show();

	return app.exec();
}
