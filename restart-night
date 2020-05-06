#!/bin/csh -f
cd /clients/Islandia/lib
mv islandia.db islandia.db.old
if(-r islandia.db.new) then
	mv islandia.db.new islandia.db
else
	cp islandia.db.old islandia.db
endif

cp ../bin/netmud.conc netmud.c
cp ../bin/concentrate .
if(-r connect.night) cp connect.night connect.txt
if(-r motd.night) cp motd.night motd.txt
echo RESTARTED AT `date` >> islandia.log
nice netmud.c islandia.db islandia.db.new >>& islandia.log &
