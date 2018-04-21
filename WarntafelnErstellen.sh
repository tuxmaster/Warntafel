#!/bin/bash
BIN_PATH=$(grep DESTDIR Warntafel.pro | cut -d'=' -f2)
./GefahrgutnummernDBerstellen.sh $BIN_PATH
./UN-NummernDBerstellen.sh $BIN_PATH
