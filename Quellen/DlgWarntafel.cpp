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

#include "DlgWarntafel.h"
#include "Kennzahltester.h"
#include <QtGui>

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
		Q_EMIT DatenStimmig();
}
void DlgWarntafel::Fehler(const QString &fehler)
{
	QObject* Absender =sender();
	Absender->disconnect(this,SLOT(Fehler(QString)));
	QMessageBox::critical(this,tr("Fehler"),fehler);
}
