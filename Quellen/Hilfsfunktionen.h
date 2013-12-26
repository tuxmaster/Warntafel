/*
	Copyright (C) 2013-2014 Frank Büttner frank-buettner@gmx.net

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

#ifndef HILFSFUNKTIONEN_H
#define HILFSFUNKTIONEN_H

#include <QObject>

class QMainWindow;
class Hilfsfunktionen : public QObject
{
		Q_OBJECT
	public:
		explicit Hilfsfunktionen(QObject *eltern = 0);
		static void FensterZentrieren(QMainWindow *fenster);

	signals:

	public slots:

};

#endif // HILFSFUNKTIONEN_H
