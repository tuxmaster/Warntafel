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
QT      += core gui network sql svg
CONFIG  += warn_on

TARGET = Warntafeln
UI_DIR=tmp/ui
MOC_DIR=tmp/moc
OBJECTS_DIR=tmp/obj
RCC_DIR=tmp/rcc

Doku.commands = doxygen
Doku.depends = $(TARGET)

GefahrenZettel.commands = ./GefahrenzettelErstellen.sh
GefahrenZettel.depends = $(TARGET)

Warntafel.commands = ./WarntafelnErstellen.sh
Warntafel.depends = $(TARGET)

QMAKE_EXTRA_TARGETS += Doku GefahrenZettel Warntafel

HEADERS += \
    Quellen/DlgHaupt.h \
    Quellen/Vorgaben.h \
    Quellen/Modellgefahrgutklasse.h \
    Quellen/DlgGefahrensymbol.h \
    Quellen/DlgWarntafel.h \
    Quellen/DlgWarntafelAnzeigen.h \
    Quellen/Gefahrkennzahltester.h

SOURCES += \
    Quellen/DlgHaupt.cpp \
    Quellen/Start.cpp \
    Quellen/Modellgefahrgutklasse.cpp \
    Quellen/DlgGefahrensymbol.cpp \
    Quellen/DlgWarntafel.cpp \
    Quellen/DlgWarntafelAnzeigen.cpp \
    Quellen/Gefahrkennzahltester.cpp

FORMS += \
    Dialoge/Hauptfenster.ui \
    Dialoge/Gefahrensymbol.ui \
    Dialoge/Warntafel.ui \
    Dialoge/WarntafelAnzeigen.ui

TRANSLATIONS +=Übersetzungen/Warntafel_en.ts

RESOURCES += \
    Resourcen.qrc

OTHER_FILES += Gefahrenzettel.qrc \
    Doxyfile
