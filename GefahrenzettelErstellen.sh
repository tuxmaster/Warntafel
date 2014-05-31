#! /bin/bash
./GefahrenzettelDBerstellen.sh
if [ -e /usr/bin/rcc-qt5 ]; then
	echo Nehme Qt5
	rcc-qt5 -binary Gefahrenzettel.qrc -o Gefahrenzettel.rcc
else
	echo Nehme Qt4
	rcc -binary Gefahrenzettel.qrc -o Gefahrenzettel.rcc
fi
