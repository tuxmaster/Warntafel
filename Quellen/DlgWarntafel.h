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

#ifndef DLGWARNTAFEL_H
#define DLGWARNTAFEL_H

#include "ui_Warntafel.h"

class DlgWarntafel : public QWidget, private Ui::DlgWarntafel
{
		Q_OBJECT

	public:
		explicit	DlgWarntafel(QWidget *eltern = 0);

	private Q_SLOTS:


	protected:
		void		changeEvent(QEvent *e);
};

#endif // DLGWARNTAFEL_H
