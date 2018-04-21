#!/bin/bash
if [ "$1" == "android" ];then
        BIN_PATH="tmp/resourcen/assets"
else
        BIN_PATH=$(grep DESTDIR Warntafel.pro | cut -d'=' -f2)
fi
./GefahrgutnummernDBerstellen.sh $BIN_PATH
./UN-NummernDBerstellen.sh $BIN_PATH
