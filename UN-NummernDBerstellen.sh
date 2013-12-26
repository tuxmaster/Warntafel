#! /bin/bash
# Erstellen mit: sqlite3 UN-Nummern.dat ".dump UN_Nummern" > UN-Nummern.sql
Datei="UN-Nummern.dat"
rm -f $Datei 2>/dev/null
sqlite3 $Datei < UN-Nummern.sql
