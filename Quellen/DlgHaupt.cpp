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
#include "DlgHaupt.h"
#include <QtGui>
#include <QtSql>
#include "Vorgaben.h"
#include "Modellgefahrgutklasse.h"

DlgHaupt::DlgHaupt(QWidget *eltern) :QMainWindow(eltern)
{
	setupUi(this);
	InDieMitte();
	// Wenn kein SQlite da ist, braucht man nicht weitermachen
	if(!QSqlDatabase::isDriverAvailable("QSQLITE"))
	{
		Fehler(trUtf8("Das Qt SQLite Modul ist nicht verfügbar. Ohne dieses ist ein Start nicht möglich."));
		return;
	}
	tbGefahrenzettel->setModel(new ModellGefahrgutklasse(this));
}
void DlgHaupt::InDieMitte()
{
	QDesktopWidget *Arbeitsplatz = QApplication::desktop();

	int Bildschirmbreite, Breite;
	int Bildschirmhoehe, Hoehe;
	int x, y;
	QSize Fenstergroesse;

	Bildschirmbreite = Arbeitsplatz->width();
	Bildschirmhoehe = Arbeitsplatz->height();

	Fenstergroesse = size();
	Breite = Fenstergroesse.width();
	Hoehe = Fenstergroesse.height();

	x = (Bildschirmbreite - Breite) / 2;
	y = (Bildschirmhoehe - Hoehe) / 2;
	//y -= 50;
	move ( x, y );
}

void DlgHaupt::changeEvent(QEvent *e)
{
	QMainWindow::changeEvent(e);
	switch (e->type())
	{
		case QEvent::LanguageChange:
				retranslateUi(this);
				break;
		default:
				break;
	}
}
void DlgHaupt::Fehler(const QString &fehler)
{
	QMessageBox::critical(this,tr("Fehler"),fehler);
	exit(-1);
}

void DlgHaupt::on_sfInfo_clicked()
{
	StapelFunktionen->setCurrentWidget(Infoseite);
}
void DlgHaupt::on_sfWarntafel_clicked()
{
	StapelFunktionen->setCurrentWidget(Warntafel);
}
void DlgHaupt::on_sfGefahrzettel_clicked()
{
	StapelFunktionen->setCurrentWidget(Gefahrzettel);
}

void DlgHaupt::on_sfUeberQt_clicked()
{
	QMessageBox::aboutQt(this,trUtf8("Über Qt"));
}
void DlgHaupt::on_sfUeberWarntafel_clicked()
{
	QMessageBox::information(this,trUtf8("Über %1").arg(PROGRAMM),tr("Version: %1").arg(VERSION));
}
