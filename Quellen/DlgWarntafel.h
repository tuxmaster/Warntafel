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

#ifndef DLGWARNTAFEL_H
#define DLGWARNTAFEL_H

#include "ui_Warntafel.h"

class DlgWarntafel : public QWidget, private Ui::DlgWarntafel
{
		Q_OBJECT

	public:
		explicit				DlgWarntafel(QWidget *eltern = Q_NULLPTR);

	Q_SIGNALS:
		void					DatenStimmig(const QString &gefahr,const QString &stoff);
		void					Datenbankfehler(const QString &meldung);

	private:
		void					TexteLaden();
		void					SQLFehler(const QString &db,const QString &fehler);

	private Q_SLOTS:
		void					on_txtUN_Nummer_returnPressed();
		void					Fehler(const QString &fehler);

	protected:
		void					changeEvent(QEvent *e) Q_DECL_OVERRIDE;
};

#endif // DLGWARNTAFEL_H
