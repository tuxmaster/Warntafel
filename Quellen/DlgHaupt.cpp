#include "Quellen/DlgHaupt.h"

DlgHaupt::DlgHaupt(QWidget *eltern) :QMainWindow(eltern)
{
	setupUi(this);
}

void DlgHaupt::changeEvent(QEvent *e)
{
	QMainWindow::changeEvent(e);
	switch (e->type())
	{
		case QEvent::LanguageChange:
				retranslateUi(this);
				break;
		default:
				break;
	}
}
