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

#ifndef GEFAHRKENNZAHLTESTER_H
#define GEFAHRKENNZAHLTESTER_H

#include <QtCore>
#include <QValidator>

class Kennzahltester : public QValidator
{
		Q_OBJECT
	public:
		Kennzahltester(bool unnummer,QObject* eltern=Q_NULLPTR);
		QValidator::State validate(QString &eingabe, int &) const;

	Q_SIGNALS:
		void	Fehler(const QString &Fehler) const;

	private:
		void	FehlerAufgetreten(const QString &fehler)const;
		bool	K_UNNummer;
		QString	K_Tabelle;
		QString	K_Datenbank;
};

#endif // GEFAHRKENNZAHLTESTER_H
