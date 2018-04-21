#!/bin/bash
if [ "$1" == "android" ];then
	BIN_PATH="tmp/resourcen/assets"
else
	BIN_PATH=$(grep DESTDIR Warntafel.pro | cut -d'=' -f2)
fi
./GefahrenzettelDBerstellen.sh $BIN_PATH
if [ -e /usr/bin/rcc-qt5 ]; then
	rcc-qt5 -binary Gefahrenzettel.qrc -o ${BIN_PATH}/Gefahrenzettel.rcc
else
	rcc -binary Gefahrenzettel.qrc -o ${BIN_PATH}/Gefahrenzettel.rcc
fi
