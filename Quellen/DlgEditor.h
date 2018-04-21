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

#ifndef DLGEDITOR_H
#define DLGEDITOR_H

#include <QFileDialog>
#include <QProcess>

#include "ui_Editor.h"

class QSqlTableModel;

class DlgEditor : public QMainWindow, private Ui::DlgEditor
{
		Q_OBJECT

	public:
		explicit			DlgEditor(QWidget *eltern = Q_NULLPTR);

	private:

		QSqlTableModel*		K_UNNummernmodell;
		QSqlTableModel*		K_Gefahrenzettelmodell;
		QSqlTableModel*		K_Gefahrgutnummernmodell;
		QFileDialog*		K_Dateiauswahl;
		QProcess*			K_Prozess;

	private Q_SLOTS:
		void				Fehler(const QString &fehler) __attribute__ ((noreturn));

		void				on_sfGefahrenzettelpfad_clicked();
		void				on_sfGefahrgutnummernpfad_clicked();
		void				on_sfUNNummernpfad_clicked();
		void				on_sfSymbolfpad_clicked();

		void				on_action_DatenbankenAktivieren_triggered();
		void				on_action_SymboleAktivieren_triggered();

		void				on_action_GefahrgutklasseLaden_triggered();
		void				on_action_GefahrgutklasseSpeichern_triggered();
		void				on_action_GefahrgutklasseKompilieren_triggered();

		void				on_action_GefahrenzettelLaden_triggered();
		void				on_action_StoffgruppenLaden_triggered();
		void				on_action_UN_NummernLaden_triggered();

		void				on_action_GefahrenzettelSpeichern_triggered();
		void				on_action_StoffgruppenSpeichern_triggered();
		void				on_action_UN_NummernSpeichern_triggered();

		void				on_sfZeileEinfuegen_clicked();
		void				on_sfZeileLoeschen_clicked();

		void				ProzessFertig(int rueckgabe, QProcess::ExitStatus);

	protected:
		void				changeEvent(QEvent *e) Q_DECL_OVERRIDE;
		void				closeEvent (QCloseEvent *e) Q_DECL_OVERRIDE;
};

#endif // DLGEDITOR_H
