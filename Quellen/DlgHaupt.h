#ifndef DLGHAUPT_H
#define DLGHAUPT_H

#include "ui_Hauptfenster.h"

class DlgHaupt : public QMainWindow, private Ui::Hauptfenster
{
		Q_OBJECT
	public:
		explicit DlgHaupt(QWidget *eltern = 0);

	protected:
		void changeEvent(QEvent *e);
};

#endif // DLGHAUPT_H
