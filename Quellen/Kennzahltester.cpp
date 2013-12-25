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

#include "Kennzahltester.h"
#include "Vorgaben.h"
#include <QtSql>

Kennzahltester::Kennzahltester(bool unnummer,QObject *eltern):QValidator(eltern)
{
	K_UNNummer=unnummer;
	if(K_UNNummer)
	{
		K_Datenbank=UNNUMMERNDB;
		K_Tabelle="UNNummern";
	}
	else
	{
			K_Datenbank=GEFAHRGUTNUMMERNDB;
			K_Tabelle="Gefahrgutnummern";
	}
}
QValidator::State Kennzahltester::validate(QString &eingabe, int &) const
{
	if(eingabe.isEmpty())
		return QValidator::Intermediate;
	if(eingabe.size()>4)
		return QValidator::Invalid;
	//Wenn der Eintrag in der DB ist, dann gültig, sonst mittendrin
	QSqlDatabase DB = QSqlDatabase::database(K_Datenbank);
	QSqlQuery Abfrage(DB);
	if(!Abfrage.prepare(QString("select Nummer from %1 where Nummer like ?").arg(K_Tabelle)))
	{
		FehlerAufgetreten(Abfrage.lastError().text());
		return QValidator::Invalid;
	}
	Abfrage.bindValue(0,QString("%1%").arg(eingabe));
	if(!Abfrage.exec())
	{
		FehlerAufgetreten(Abfrage.lastError().text());
		return QValidator::Invalid;
	}
	while (Abfrage.next())
		return QValidator::Acceptable;
	return QValidator::Invalid;
}
void Kennzahltester::FehlerAufgetreten(const QString &fehler) const
{
	Q_EMIT Fehler(tr("Datenbankfehler %1.\n%2").arg(K_Tabelle).arg(fehler));
}
