#include <QtGui>
#include "DlgHaupt.h"

int main(int argc, char *argv[])
{
		QApplication Qt(argc, argv);
		QTranslator QtUebersetzung;
		QtUebersetzung.load(QString("qt_%1").arg(QLocale::system().name()),QLibraryInfo::location(QLibraryInfo::TranslationsPath));
		Qt.installTranslator(&QtUebersetzung);
		DlgHaupt Haupt;
		Haupt.show();
		return Qt.exec();
}
