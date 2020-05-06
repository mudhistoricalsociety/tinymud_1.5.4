#!/bin/csh -f
#
# This script assumes you have the following structure:
#
#	$HOME/bin	executable MUD programs
#	$HOME/lib	database files, daily logs
#	$HOME/src	source code for netmud
#

cd /usr/tinymud/lib
mv tinymud.db tinymud.db.old
if(-r tinymud.db.new) then
	mv tinymud.db.new tinymud.db
else
	cp tinymud.db.old tinymud.db
endif

# Use netmud instead of netmud.conc if you don't want the port concentrator
cp ../bin/netmud.conc netmud.exe
cp ../bin/concentrate concentrate

echo RESTARTED AT `date` >> tinymud.log
./netmud.exe tinymud.db tinymud.db.new >>& tinymud.log &
