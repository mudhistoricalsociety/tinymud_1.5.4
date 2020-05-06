#!/bin/csh -f

set WINNER = `rpick < lottery`

echo "Starting Daytime Islandia, lottery winner is $WINNER..."

cd /clients/Islandia/lib
if(-r islandia.db.new) then
	set input = islandia.db.new
else
	set input = islandia.db
endif

cp /dev/null connect.txt
if(-r connect.day) cp connect.day connect.txt
if(-r motd.day) cp motd.day motd.txt

echo "" >> motd.txt
echo "		Today's Lottery Winner is $WINNER" >> motd.txt
echo "" >> motd.txt

../bin/extract norecycle reachable players b1370 \
	-274 -560 -809 1384 1403 1404 1406 1505 \
	Tinker Lynx Tygling Three Janitor Mav \
	$WINNER \
	< $input > day.db

cp ../bin/netmud netmud.r
echo RESTARTED DAY VERSION AT `date` >> islandia.log
netmud.r day.db day.db.new >>& islandia.log &
