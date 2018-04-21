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
#include <QtGui>
#include <QtSql>

#include "Modellgefahrgutklasse.h"
#include "Vorgaben.h"

ModellGefahrgutklasse::ModellGefahrgutklasse(QObject *eltern) :QAbstractTableModel(eltern)
{
	QSqlDatabase DB = QSqlDatabase::addDatabase("QSQLITE",GEFAHRENZETTELDB);
	K_SQLDaten=Q_NULLPTR;
	DB.setDatabaseName(QString("%1/%2").arg(GEFAHRENZETTELPFAD).arg(GEFAHRENZETTEL));
	if(!DB.open())
	{
		K_Hilfsfehlertext=trUtf8("Fehler beim Öffnen der Datenbank %1.\n%2").arg(QString("%1/%2").arg(GEFAHRENZETTELPFAD).arg(GEFAHRENZETTEL))
																			.arg(DB.lastError().text());
		QTimer::singleShot(0,this,SLOT(Hilfsfehler()));
	}
	else
	{
		if (!QResource::registerResource(QString("%1/%2").arg(GEFAHRENZETTELPFAD).arg(GEFAHRENZETTELSYMBOL)))
		{
			K_Hilfsfehlertext=tr("Konnte die Datei %1 mit den Symbolen nicht laden.").arg(QString("%1/%2").arg(GEFAHRENZETTELPFAD).arg(GEFAHRENZETTELSYMBOL));
			QTimer::singleShot(0,this,SLOT(Hilfsfehler()));
			return;
		}
		K_SQLDaten=new QSqlTableModel(this, DB);
		K_SQLDaten->setTable("Zettel");
		K_SQLDaten->select();
	}
}
void ModellGefahrgutklasse::Hilfsfehler()
{
	Q_EMIT Fehler(K_Hilfsfehlertext);
}

int ModellGefahrgutklasse::rowCount(const QModelIndex &) const
{
	if(K_SQLDaten)
		return K_SQLDaten->rowCount();
	return 0;
}
QVariant ModellGefahrgutklasse::data(const QModelIndex &index, int rolle) const
{
	switch(rolle)
	{
		case Qt::TextAlignmentRole:
				// Die Klassennummer soll zentiert sein.
				if(index.column()==1)
					return Qt::AlignCenter;
				else
					return QVariant();
		case Qt::DecorationRole:
				if(index.column()!=0)
					return QVariant();
				else
				{
					QPixmap Symbol;
					if (!QPixmapCache::find(K_SQLDaten->data(index).toString(),&Symbol))
					{
						Symbol.load(K_SQLDaten->data(index).toString());
						Symbol=Symbol.scaled(50,50,Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation);
						QPixmapCache::insert(K_SQLDaten->data(index).toString(),Symbol);
					}
					return Symbol;
				}
		case Qt::DisplayRole:
				if (index.column()!=0)
					return K_SQLDaten->data(index);
				else
					return QVariant();
		case Qt::ToolTipRole:
				return trUtf8("Auf das Symbol doppelt klicken um es zu vergrößern.");
		default:
			return QVariant();
	}
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
QString ModellGefahrgutklasse::Symbolpfad(const QModelIndex &welches) const
{
	if (!K_SQLDaten)
		return QString();
	return K_SQLDaten->data(welches.sibling(welches.row(),0)).toString();
}
