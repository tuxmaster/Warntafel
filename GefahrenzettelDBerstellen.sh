#! /bin/bash
sqlite3 Gefahrenzettel.dat "create table Zettel( Symbol text,Klasse text, Beschreibung text,ID text unique);"
sqlite3 Gefahrenzettel.dat "insert into Zettel Values('xx.svg','1','testbeschreibung','dddddd');"
