#    Copyright (C) 2013-2018 Frank Büttner tuxmaster@users.noreply.github.com

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
QT      += core gui sql svg widgets

CONFIG  += warn_on c++14

TARGET = Warntafel
UI_DIR=tmp/ui
MOC_DIR=tmp/moc
OBJECTS_DIR=tmp/obj
RCC_DIR=tmp/rcc

DESTDIR=bin

if (linux-g++) {
    QMAKE_LFLAGS += -fuse-ld=gold
}
if (linux-clang) {
    QMAKE_LFLAGS += -flto
}

Doku.commands = doxygen
Doku.depends = $(TARGET)

android {
    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/tmp/resourcen
    GefahrenZettelDB.commands = ./GefahrenzettelErstellen.sh android
    WarntafelDB.commands = ./WarntafelnErstellen.sh android
} else {
    GefahrenZettelDB.commands = ./GefahrenzettelErstellen.sh
    WarntafelDB.commands = ./WarntafelnErstellen.sh
    HEADERS +=  Quellen/DlgEditor.h
    SOURCES +=  Quellen/DlgEditor.cpp
    FORMS   +=  Dialoge/Editor.ui
}
GefahrenZettelDB.depends = $(TARGET)
 WarntafelDB.depends = $(TARGET)

QMAKE_EXTRA_TARGETS += Doku GefahrenZettelDB WarntafelDB
PRE_TARGETDEPS += GefahrenZettelDB WarntafelDB

HEADERS += \
    Quellen/DlgHaupt.h \
    Quellen/Vorgaben.h \
    Quellen/Modellgefahrgutklasse.h \
    Quellen/DlgGefahrensymbol.h \
    Quellen/DlgWarntafel.h \
    Quellen/DlgWarntafelAnzeigen.h \
    Quellen/Kennzahltester.h \
    Quellen/Hilfsfunktionen.h

SOURCES += \
    Quellen/DlgHaupt.cpp \
    Quellen/Start.cpp \
    Quellen/Modellgefahrgutklasse.cpp \
    Quellen/DlgGefahrensymbol.cpp \
    Quellen/DlgWarntafel.cpp \
    Quellen/DlgWarntafelAnzeigen.cpp \
    Quellen/Kennzahltester.cpp \
    Quellen/Hilfsfunktionen.cpp

FORMS += \
    Dialoge/Hauptfenster.ui \
    Dialoge/Gefahrensymbol.ui \
    Dialoge/Warntafel.ui \
    Dialoge/WarntafelAnzeigen.ui


TRANSLATIONS +=Übersetzungen/Warntafel_en.ts

RESOURCES += \
    Resourcen.qrc

OTHER_FILES += Gefahrenzettel.qrc \
    Doxyfile \
    Warntafel.desktop
