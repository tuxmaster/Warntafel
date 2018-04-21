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
#include <QWidget>
#include <QMessageBox>
#include <QtGui>
#include <QtSql>

#include "DlgHaupt.h"
#include "Vorgaben.h"
#include "Hilfsfunktionen.h"
#include "Modellgefahrgutklasse.h"
#include "DlgGefahrensymbol.h"
#include "DlgWarntafel.h"
#include "DlgWarntafelAnzeigen.h"

DlgHaupt::DlgHaupt(QWidget *eltern) :QMainWindow(eltern)
{
	setupUi(this);
	Hilfsfunktionen::FensterZentrieren(this);
	// Wenn kein SQlite da ist, braucht man nicht weitermachen
	if(!QSqlDatabase::isDriverAvailable("QSQLITE"))
		Fehler(trUtf8("Das Qt SQLite Modul ist nicht verfügbar. Ohne dieses ist ein Start nicht möglich."));
	if((!GefahenkennzahlenLaden()) || (!UNNummerLaden()))
		return;
	K_SymbolAnzeigen=new DlgGefahrensymbol(this);
	K_Gefahrgutklassemodell=new ModellGefahrgutklasse(this);
	connect(K_Gefahrgutklassemodell,SIGNAL(Fehler(QString)),this,SLOT(Fehler(QString)));
	tbGefahrenzettel->setModel(K_Gefahrgutklassemodell);
	tbGefahrenzettel->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	tbGefahrenzettel->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	connect(tbGefahrenzettel,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(GefahrenzettelSymbolAnzeige(QModelIndex)));

	K_Warntafel=new DlgWarntafel(this);
	K_TafelZeigen=new DlgWarntafelAnzeigen(this);
	connect(K_Warntafel,SIGNAL(DatenStimmig(QString,QString)),this,SLOT(TafelAusgefuellt(QString,QString)));
	connect(K_Warntafel,SIGNAL(Datenbankfehler(QString)),this,SLOT(Fehler(QString)));
	QVBoxLayout *Ansicht=new QVBoxLayout(Warntafel);
	Ansicht->addWidget(K_Warntafel);
	Warntafel->setLayout(Ansicht);
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
	exit(1);
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
void DlgHaupt::GefahrenzettelSymbolAnzeige(const QModelIndex &welches)
{
	//Nur die erste Spalte zählt:)
	if(welches.column()!=0)
		return;
	else
	{
		K_SymbolAnzeigen->SymbolSetzen(K_Gefahrgutklassemodell->Symbolpfad(welches));
		K_SymbolAnzeigen->exec();
	}
}
void DlgHaupt::TafelAusgefuellt(const QString &gefahr,const QString &stoff)
{
	K_TafelZeigen->TextSetzen(gefahr,stoff);
	K_TafelZeigen->exec();
}
bool DlgHaupt::GefahenkennzahlenLaden()
{
	QSqlDatabase DB = QSqlDatabase::addDatabase("QSQLITE",GEFAHRGUTNUMMERNDB);
	DB.setDatabaseName(QString("%1/%2").arg(GEFAHRGUTNUMMERNPFAD).arg(GEFAHRGUTNUMMERN));
	if(!DB.open())
		Fehler(trUtf8("Konnte die Gefahrennummern nicht laden.\n%1").arg(DB.lastError().text()));
	return true;
}
bool DlgHaupt::UNNummerLaden()
{
	QSqlDatabase DB = QSqlDatabase::addDatabase("QSQLITE",UNNUMMERNDB);
	DB.setDatabaseName(QString("%1/%2").arg(UNNUMMERNPFAD).arg(UNNUMMERN));
	if(!DB.open())
		Fehler(trUtf8("Konnte die UN Nummern nicht laden.\n%1").arg(DB.lastError().text()));
	return true;
}
