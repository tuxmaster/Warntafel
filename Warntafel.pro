#    Copyright (C) 2013-2014 Frank Büttner frank-buettner@gmx.net

#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.

#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.

#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>
#
QT       += core gui network sql
TARGET = Warntafeln
UI_DIR=tmp/ui
MOC_DIR=tmp/moc
OBJECTS_DIR=tmp/obj
RCC_DIR=tmp/rcc

HEADERS += \
    Quellen/DlgHaupt.h \
    Quellen/Vorgaben.h \
    Quellen/Modellgefahrgutklasse.h

SOURCES += \
    Quellen/DlgHaupt.cpp \
    Quellen/Start.cpp \
    Quellen/Modellgefahrgutklasse.cpp

FORMS += \
    Dialoge/Hauptfenster.ui

TRANSLATIONS +=Übersetzungen/Warntafel_en.ts

RESOURCES += \
    Resourcen.qrc
