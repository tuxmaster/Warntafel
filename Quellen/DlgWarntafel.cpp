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

#include <QtGui>
#include <QtSql>

#include "Vorgaben.h"
#include "DlgWarntafel.h"
#include "Kennzahltester.h"

DlgWarntafel::DlgWarntafel(QWidget *eltern) :QWidget(eltern)
{
	setupUi(this);
	Kennzahltester *Gefahrtester=new Kennzahltester(false,this);
	Kennzahltester *UNNummertest=new Kennzahltester(true,this);
	connect(Gefahrtester,SIGNAL(Fehler(QString)),this,SLOT(Fehler(QString)));
	connect(UNNummertest,SIGNAL(Fehler(QString)),this,SLOT(Fehler(QString)));
	txtUN_Nummer->setValidator(UNNummertest);
	txtGefahrgutnummer->setValidator(Gefahrtester);
}

void DlgWarntafel::changeEvent(QEvent *e)
{
	QWidget::changeEvent(e);
	switch (e->type())
	{
		case QEvent::LanguageChange:
			retranslateUi(this);
			break;
		default:
			break;
	}
}
void DlgWarntafel::on_txtUN_Nummer_returnPressed()
{
	if(txtGefahrgutnummer->hasAcceptableInput())
		TexteLaden();
}
void DlgWarntafel::Fehler(const QString &fehler)
{
	QObject* Absender =sender();
	Absender->disconnect(this,SLOT(Fehler(QString)));
	QMessageBox::critical(this,tr("Fehler"),fehler);
}
void DlgWarntafel::TexteLaden()
{
	QSqlDatabase DB_Gefahr = QSqlDatabase::database(GEFAHRGUTNUMMERNDB,false);
	QSqlDatabase DB_Stoff = QSqlDatabase::database(UNNUMMERNDB,false);

	QString Gefahr;
	QString Stoff;

	if(!DB_Gefahr.isValid())
	{
		SQLFehler("Gefahrgutnummer",DB_Gefahr.lastError().text());
		return;
	}
	if(!DB_Stoff.isValid())
	{
		SQLFehler("UNNummern",DB_Stoff.lastError().text());
		return;
	}
	QSqlQuery Abfrage(DB_Gefahr);
	if(!Abfrage.prepare(QString("select Beschreibung from Gefahrgutnummern where Nummer = ?")))
	{
		SQLFehler("Gefahrgutnummer",Abfrage.lastError().text());
		return;
	}
	Abfrage.bindValue(0,txtGefahrgutnummer->text().toUpper());
	if(!Abfrage.exec())
	{
		SQLFehler("Gefahrgutnummer",Abfrage.lastError().text());
		return;
	}
	while (Abfrage.next())
		Gefahr=Abfrage.value(0).toString();

	Abfrage=QSqlQuery(DB_Stoff);
	if(!Abfrage.prepare(QString("select Beschreibung from UN_Nummern where Nummer = ?")))
	{
		SQLFehler("UN Nummer",Abfrage.lastError().text());
		return;
	}
	Abfrage.bindValue(0,txtUN_Nummer->text().toInt());
	if(!Abfrage.exec())
	{
		SQLFehler("UN Nummer",Abfrage.lastError().text());
		return;
	}
	while (Abfrage.next())
		Stoff=Abfrage.value(0).toString();

	Q_EMIT DatenStimmig(Gefahr,Stoff);
}
void DlgWarntafel::SQLFehler(const QString &db, const QString &fehler)
{
	Q_EMIT Datenbankfehler(tr("Fehler beim Zugriff die die %1 Datenbank.\n%2").arg(db).arg(fehler));
}
