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

#ifndef DLGGEFAHRENSYMBOL_H
#define DLGGEFAHRENSYMBOL_H

#include "ui_Gefahrensymbol.h"

class QSvgWidget;
class DlgGefahrensymbol : public QDialog, private Ui::DlgGefahrensymbol
{
		Q_OBJECT

	public:
		explicit	DlgGefahrensymbol(QWidget *eltern = Q_NULLPTR);
		void		SymbolSetzen(const QString &dateiname);

	private:
		QSvgWidget	*K_Symbolanzeige;

	protected:
		void		changeEvent(QEvent *e) Q_DECL_OVERRIDE;
};

#endif // DLGGEFAHRENSYMBOL_H
