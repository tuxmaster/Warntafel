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

#ifndef MODELLGEFAHRGUTKLASSE_H
#define MODELLGEFAHRGUTKLASSE_H

#include <QtCore>

class QSqlTableModel;
class ModellGefahrgutklasse : public QAbstractTableModel
{
		Q_OBJECT
	public:
		explicit		ModellGefahrgutklasse(QObject *eltern = Q_NULLPTR);
		int				rowCount(const QModelIndex &) const ;
		int				columnCount(const QModelIndex &) const{return 3;}
		QVariant		data(const QModelIndex &index, int rolle) const;
		QVariant		headerData(int bereich, Qt::Orientation ausrichtung, int rolle) const;
		QString			Symbolpfad(const QModelIndex &welches)const;

	Q_SIGNALS:
		void			Fehler(const QString &fehler) const;

	private Q_SLOTS:
		void			Hilfsfehler();

	private:
		QSqlTableModel*	K_SQLDaten;
		QString			K_Hilfsfehlertext;


};

#endif // MODELLGEFAHRGUTKLASSE_H
