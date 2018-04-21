#!/bin/bash
./GefahrenzettelDBerstellen.sh
if [ -e /usr/bin/rcc-qt5 ]; then
	rcc-qt5 -binary Gefahrenzettel.qrc -o Gefahrenzettel.rcc
else
	rcc -binary Gefahrenzettel.qrc -o Gefahrenzettel.rcc
fi
