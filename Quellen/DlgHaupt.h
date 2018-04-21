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
#ifndef DLGHAUPT_H
#define DLGHAUPT_H

#include "ui_Hauptfenster.h"

class ModellGefahrgutklasse;
class DlgGefahrensymbol;
class DlgWarntafel;
class DlgWarntafelAnzeigen;
class DlgHaupt : public QMainWindow, private Ui::Hauptfenster
{
		Q_OBJECT
	public:
		explicit	DlgHaupt(QWidget *eltern = Q_NULLPTR);

	private Q_SLOTS:
		void					on_sfInfo_clicked();
		void					on_sfWarntafel_clicked();
		void					on_sfGefahrzettel_clicked();
		void					on_sfUeberQt_clicked();
		void					on_sfUeberWarntafel_clicked();

	private:
		bool					GefahenkennzahlenLaden();
		bool					UNNummerLaden();
		ModellGefahrgutklasse	*K_Gefahrgutklassemodell;
		DlgGefahrensymbol		*K_SymbolAnzeigen;
		DlgWarntafel			*K_Warntafel;
		DlgWarntafelAnzeigen	*K_TafelZeigen;

	private Q_SLOTS:
		void					Fehler(const QString &fehler) __attribute__ ((noreturn));
		void					GefahrenzettelSymbolAnzeige(const QModelIndex &welches);
		void					TafelAusgefuellt(const QString &gefahr,const QString &stoff);

	protected:
		void					changeEvent(QEvent *e) Q_DECL_OVERRIDE;
};

#endif // DLGHAUPT_H
