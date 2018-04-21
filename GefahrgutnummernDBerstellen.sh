#!/bin/bash
#Erstellen: sqlite3 Gefahrgutnummern.dat ".dump Gefahrgutnummern" > Gefahrgutnummern.sql
Datei="${1}/Gefahrgutnummern.dat"
rm -f $Datei 2>/dev/null
sqlite3 $Datei < Gefahrgutnummern.sql
