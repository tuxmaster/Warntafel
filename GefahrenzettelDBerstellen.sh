#! /bin/bash
# Erstellen mit: sqlite3 Gefahrenzettel.dat ".dump Zettel" > Gefahrenzettel.sql
Datei="Gefahrenzettel.dat"
rm -f $Datei 2>/dev/null
sqlite3 $Datei < Gefahrenzettel.sql
