#include "Quellen/DlgHaupt.h"

Hauptfenster::Hauptfenster(QWidget *parent) :
	QMainWindow(parent)
{
	setupUi(this);
}

void Hauptfenster::changeEvent(QEvent *e)
{
	QMainWindow::changeEvent(e);
	switch (e->type()) {
		case QEvent::LanguageChange:
			retranslateUi(this);
			break;
		default:
			break;
	}
}
