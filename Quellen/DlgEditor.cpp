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

#include <QtGui>
#include <QtSql>

#include "DlgEditor.h"
#include "Vorgaben.h"
#include "Hilfsfunktionen.h"

DlgEditor::DlgEditor(QWidget *eltern) :	QMainWindow(eltern)
{
	setupUi(this);
	Hilfsfunktionen::FensterZentrieren(this);

	if(!QSqlDatabase::isDriverAvailable("QSQLITE"))
	{
		Fehler(trUtf8("Das Qt SQLite Modul ist nicht verfügbar. Ohne dieses ist ein Start nicht möglich."));
		return;
	}

	K_Dateiauswahl=new QFileDialog(this);
	K_Dateiauswahl->setDirectory(GEFAHRENZETTELPFAD);

	txtGefahrenzettel->setText(QString("%1%2").arg(GEFAHRENZETTELPFAD).arg(GEFAHRENZETTEL));
	txtGefahrgutnummern->setText(QString("%1%2").arg(GEFAHRGUTNUMMERNPFAD).arg(GEFAHRGUTNUMMERN));
	txtUNNummern->setText(QString("%1%2").arg(UNNUMMERNPFAD).arg(UNNUMMERN));

	K_UNNummernmodell=0;
	K_Gefahrenzettelmodell=0;
	K_Gefahrgutnummernmodell=0;

	Tabelle->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
}

void DlgEditor::changeEvent(QEvent *e)
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
void DlgEditor::on_sfGefahrenzettelpfad_clicked()
{
	if(K_Dateiauswahl->exec())
		txtGefahrenzettel->setText(K_Dateiauswahl->selectedFiles()[0]);
}
void DlgEditor::on_sfGefahrgutnummernpfad_clicked()
{
	if(K_Dateiauswahl->exec())
		txtGefahrgutnummern->setText(K_Dateiauswahl->selectedFiles()[0]);
}
void DlgEditor::on_sfUNNummernpfad_clicked()
{
	if(K_Dateiauswahl->exec())
		txtUNNummern->setText(K_Dateiauswahl->selectedFiles()[0]);
}
void DlgEditor::on_action_GefahrenzettelLaden_triggered()
{
	if(!K_Gefahrenzettelmodell)
	{
		QSqlDatabase DB = QSqlDatabase::addDatabase("QSQLITE",GEFAHRENZETTELDB);
		DB.setDatabaseName(txtGefahrenzettel->text());
		if(!DB.open())
		{
			Fehler(trUtf8("Konnte die Gefahentafel DB nicht laden.\n%1").arg(DB.lastError().text()));
			Tabelle->setModel(0);
			return;
		}
		K_Gefahrenzettelmodell=new QSqlTableModel(this,DB);
		K_Gefahrenzettelmodell->setTable("Zettel");
		K_Gefahrenzettelmodell->setEditStrategy(QSqlTableModel::OnManualSubmit);
		K_Gefahrenzettelmodell->select();
	}
	Tabelle->setModel(K_Gefahrenzettelmodell);
}
void DlgEditor::on_action_StoffgruppenLaden_triggered()
{
	if(!K_Gefahrgutnummernmodell)
	{
		QSqlDatabase DB = QSqlDatabase::addDatabase("QSQLITE",GEFAHRGUTNUMMERNDB);
		DB.setDatabaseName(txtGefahrgutnummern->text());
		if(!DB.open())
		{
			Fehler(trUtf8("Konnte die Stoffruppen DB laden.\n%1").arg(DB.lastError().text()));
			Tabelle->setModel(0);
			return;
		}
		K_Gefahrgutnummernmodell=new QSqlTableModel(this,DB);
		K_Gefahrgutnummernmodell->setTable("Gefahrgutnummern");
		K_Gefahrgutnummernmodell->setEditStrategy(QSqlTableModel::OnManualSubmit);
		K_Gefahrgutnummernmodell->select();
	}
	Tabelle->setModel(K_Gefahrgutnummernmodell);
}
void DlgEditor::on_action_UN_NummernLaden_triggered()
{
	if(!K_UNNummernmodell)
	{
		QSqlDatabase DB = QSqlDatabase::addDatabase("QSQLITE",UNNUMMERNDB);
		DB.setDatabaseName(txtUNNummern->text());
		if(!DB.open())
		{
			Fehler(trUtf8("Konnte die UN Nummern DB laden.\n%1").arg(DB.lastError().text()));
			Tabelle->setModel(0);
			return;
		}
		K_UNNummernmodell=new QSqlTableModel(this,DB);
		K_UNNummernmodell->setTable("UN_Nummern");
		K_UNNummernmodell->setEditStrategy(QSqlTableModel::OnManualSubmit);
		K_UNNummernmodell->select();
	}
	Tabelle->setModel(K_UNNummernmodell);
}
void DlgEditor::on_action_GefahrenzettelSpeichern_triggered()
{
	if(!K_Gefahrenzettelmodell)
		return;
	if(!K_Gefahrenzettelmodell->submitAll())
		Fehler(K_Gefahrenzettelmodell->lastError().text());
}
void DlgEditor::on_action_StoffgruppenSpeichern_triggered()
{
	if(!K_Gefahrgutnummernmodell)
		return;
	if(!K_Gefahrgutnummernmodell->submitAll())
		Fehler(K_Gefahrgutnummernmodell->lastError().text());
}
void DlgEditor::on_action_UN_NummernSpeichern_triggered()
{
	if(!K_UNNummernmodell)
		return;
	if(!K_UNNummernmodell->submitAll())
		Fehler(K_UNNummernmodell->lastError().text());
}

void DlgEditor::Fehler(const QString &fehler)
{
	QMessageBox::critical(this,tr("Fehler"),fehler);
	exit(1);
}
void DlgEditor::closeEvent(QCloseEvent *e)
{
	//nur fragen wenn was gemacht wurde
	if((!K_Gefahrenzettelmodell) && (!K_Gefahrgutnummernmodell) && (!K_UNNummernmodell))
		e->accept();
	else if(QMessageBox::question(this,tr("Beenden"),trUtf8("Alle nicht gepeicherten Änderungen gehen verloren.\nSind Sie sicher?"),
								 QMessageBox::Yes|QMessageBox::No,QMessageBox::No)==QMessageBox::Yes)
			e->accept();
	else
			e->ignore();
}
void DlgEditor::on_sfZeileEinfuegen_clicked()
{
	QSqlTableModel *Modell=(QSqlTableModel*)Tabelle->model();
	if(!Modell)
		return;
	else
	{
		Modell->insertRows(Modell->rowCount(),1);
		Tabelle->scrollTo(Modell->index(Modell->rowCount()-1,1));
	}
}