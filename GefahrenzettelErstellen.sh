#!/bin/bash
BIN_PATH=$(grep DESTDIR Warntafel.pro | cut -d'=' -f2)
./GefahrenzettelDBerstellen.sh $BIN_PATH
if [ -e /usr/bin/rcc-qt5 ]; then
	rcc-qt5 -binary Gefahrenzettel.qrc -o ${BIN_PATH}/Gefahrenzettel.rcc
else
	rcc -binary Gefahrenzettel.qrc -o ${BIN_PATH}/Gefahrenzettel.rcc
fi
