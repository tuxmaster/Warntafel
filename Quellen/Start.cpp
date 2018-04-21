/*
	Copyright (C) 2013-2018 Frank Büttner frank-buettner@gmx.net

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>
*/
#include <QtCore>
#include <QtWidgets>
#include <QtGui>

#include "DlgHaupt.h"
#ifndef Q_OS_ANDROID
#include "DlgEditor.h"
#endif
#include "Vorgaben.h"

int main(int argc, char *argv[])
{
		QApplication Qt(argc, argv);
		QPixmapCache::setCacheLimit(BILDPUFFER_KB);
		QTranslator QtUebersetzung;
		QTranslator ProgrammUebersetzung;
#ifndef Q_OS_ANDROID
		QString Uebersetzungspfad=QLibraryInfo::location(QLibraryInfo::TranslationsPath);
#else
		QString Uebersetzungspfad="assets:/";
#endif
		QtUebersetzung.load(QString("qt_%1").arg(QLocale::system().name()),Uebersetzungspfad);
		ProgrammUebersetzung.load(QString("%1_%2").arg(PROGRAMM).arg(QLocale::system().name()),Uebersetzungspfad);
		Qt.installTranslator(&QtUebersetzung);
		Qt.installTranslator(&ProgrammUebersetzung);
		QMainWindow *Haupt;
#ifndef Q_OS_ANDROID
		if(qApp->arguments().contains("--editor",Qt::CaseInsensitive))
			Haupt=new DlgEditor();
		else
			Haupt=new DlgHaupt();
#else
		Haupt=new DlgHaupt();
#endif
		Haupt->show();
		return Qt.exec();
}
