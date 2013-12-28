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
#endif
#include <QtGui>
#include <QtSvg>

#include "DlgGefahrensymbol.h"

DlgGefahrensymbol::DlgGefahrensymbol(QWidget *eltern) :	QDialog(eltern)
{
	setupUi(this);
	QVBoxLayout *Ansicht=new QVBoxLayout(Symbolrahmen);
	K_Symbolanzeige=new QSvgWidget(this);
	Ansicht->addWidget(K_Symbolanzeige);
	Symbolrahmen->setLayout(Ansicht);
}

void DlgGefahrensymbol::changeEvent(QEvent *e)
{
	QDialog::changeEvent(e);
	switch (e->type())
	{
		case QEvent::LanguageChange:
				retranslateUi(this);
			break;
		default:
			break;
	}
}
void DlgGefahrensymbol::SymbolSetzen(const QString &dateiname)
{
	K_Symbolanzeige->load(dateiname);
}
