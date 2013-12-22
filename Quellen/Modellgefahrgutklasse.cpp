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

#include "Modellgefahrgutklasse.h"

ModellGefahrgutklasse::ModellGefahrgutklasse(QObject *eltern) :QAbstractTableModel(eltern)
{
}
int ModellGefahrgutklasse::rowCount(const QModelIndex &eltern) const
{
	return 1;
}
QVariant ModellGefahrgutklasse::data(const QModelIndex &index, int rolle) const
{
	return QVariant();
}
QVariant ModellGefahrgutklasse::headerData(int bereich, Qt::Orientation ausrichtung, int rolle) const
{
	if ((ausrichtung==Qt::Vertical) || (rolle!=Qt::DisplayRole) )
		return QAbstractTableModel::headerData(bereich,ausrichtung,rolle);
	QString Spaltenname;
	switch (bereich)
	{
		case 0:
			Spaltenname=tr("Symbol");
			break;
		case 1:
			Spaltenname=tr("Klasse");
			break;
		case 2:
			Spaltenname=tr("Beschreibung");
			break;
		default:
			Spaltenname="";
			break;
	}
	return Spaltenname;
}
