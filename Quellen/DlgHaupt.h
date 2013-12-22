#ifndef DLGHAUPT_H
#define DLGHAUPT_H

#include "ui_Hauptfenster.h"

class Hauptfenster : public QMainWindow, private Ui::Hauptfenster
{
		Q_OBJECT

	public:
		explicit Hauptfenster(QWidget *parent = 0);

	protected:
		void changeEvent(QEvent *e);
};

#endif // DLGHAUPT_H
