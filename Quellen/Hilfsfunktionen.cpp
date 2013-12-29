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

#include <QtCore>
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
	#include <QWidget>
	#include <QDesktopWidget>
	#include <QApplication>
	#include <QLineEdit>
#endif
#include <QtGui>

#include "Hilfsfunktionen.h"

Hilfsfunktionen::Hilfsfunktionen(QObject *eltern) :	QObject(eltern)
{
}
void Hilfsfunktionen::FensterZentrieren(QMainWindow *fenster)
{
	QDesktopWidget *Arbeitsplatz = QApplication::desktop();

	int Bildschirmbreite, Breite;
	int Bildschirmhoehe, Hoehe;
	int x, y;
	QSize Fenstergroesse;

	Bildschirmbreite = Arbeitsplatz->width();
	Bildschirmhoehe = Arbeitsplatz->height();

	Fenstergroesse = fenster->size();
	Breite = Fenstergroesse.width();
	Hoehe = Fenstergroesse.height();

	x = (Bildschirmbreite - Breite) / 2;
	y = (Bildschirmhoehe - Hoehe) / 2;
	fenster->move ( x, y );
}
#if QT_VERSION >= QT_VERSION_CHECK(5,2,0)
void Hilfsfunktionen::EditorMitLoeschen(QObject *pfad)
{
	QList<QLineEdit *> Liste =pfad->findChildren<QLineEdit *>();
	Q_FOREACH (QLineEdit *Eintrag,Liste)
		Eintrag->setClearButtonEnabled(true);
}
#endif
