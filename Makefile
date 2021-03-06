#################################################################
#
# Makefile for TinyMUD source code...June 6, 1990
#
#################################################################
#
# Whatever you put in for $(CC) must be able to grok ANSI C.
#

# GCC:
#CC=gcc
#OPTIM= -g -W -Wreturn-type -Wunused -Wcomment -Wwrite-strings

# Systems with 'cc' built from GCC (IBM RT, NeXT):
CC=cc
OPTIM=-g

# Dec 3100 C compiler
#CC=cc
#OPTIM= -g -Dconst=

# 
# To log failed commands (HUH's) to stderr, include -DLOG_FAILED_COMMANDS
# To restrict object-creating commands to users with the BUILDER bit,
#   include -DRESTRICTED_BUILDING
# To log all commands, include -DLOG_COMMANDS
# To force fork_and_dump() to use vfork() instead of fork(), include 
#   -DUSE_VFORK.
# To force grow_database() to be clever about its memory management,
#   include -DDB_DOUBLING.  Use this only if your realloc does not allocate
#   in powers of 2 (if you already have a clever realloc, this option will
#   only cost you extra space).
# By default, db.c initially allocates enough space for 10000 objects, then
#   grows the space if needed.  To change this value, include
#   -DDB_INITIAL_SIZE=xxxx where xxxx is the new value (minimum 1).
# To include code for keeping track of the number of blocks allocated,
#   include -DTEST_MALLOC.
# To include code which attempts to compress string data, include -DCOMPRESS.
# To eliminate the message third parties see when a player whispers, include
#   -DQUIET_WHISPER.
# To include Stephen White's gender flags and pronoun substitution code, 
#   include -DGENDER.
# To give set (!)WIZARD and extended WHO privs only to id #1,
#   include -DGOD_PRIV.  When this option is set, two other options
#   become meanigful
#	-DGOD_MODE		Restricts host names some commands to #1
#	-DGOD_ONLY_PCREATE	Restricts @pcreate to player #1
# To have logs and WHO use hostnames instead of addresses, include
#   -DHOST_NAME.
# To have messages for connect and disconnect, include -DCONNECT_MESSAGES.
# To use a hashed player list for player name lookups, 
#   include -DPLAYER_LIST.
# To disable login-time creation of players, include -DREGISTRATION.
#    see GOD_ONLY_PCREATE above.
# To cause netmud to detach itself from the terminal on startup, include
#   -DDETACH.  The log file appears on LOG_FILE, set in config.h.
# To add the @count & @recycle command, include -DRECYCLE
# To disable core dump on errors, include -DNODUMPCORE
# To add the ROBOT flag (allowing robots to be excluded from some rooms
#   at each player's request), include -DROBOT_MODE
# To use Tinker instead of Wizard, Bobble instead of Toad, and
#    donate instead of sacrifice, include -DTINKER
# To prevent users from using confusing names
#   (currently A, An, The, You, Your, Going, Huh?), include -DNOFAKES
#
# To Use Islandia values in config.h, include -DISLANDIA
# To Use TinyHELL values in config.h, include -DTINYHELL

#DEFS= -DGOD_PRIV -DCOMPRESS -DQUIET_WHISPER -DGENDER -DHOST_NAME \
#      -DCONNECT_MESSAGES -DPLAYER_LIST -DDETACH -DREGISTRATION \
#      -DGOD_ONLY_PCREATE -DROBOT_MODE -DRECYCLE -DNOFAKES \
#      -DTINYHELL

DEFS= -DGOD_PRIV -DCOMPRESS -DQUIET_WHISPER -DGENDER -DHOST_NAME \
      -DCONNECT_MESSAGES -DPLAYER_LIST -DDETACH -DROBOT_MODE \
      -DRECYCLE -DTINKER -DNOFAKES -DISLANDIA

CFLAGS= $(OPTIM) $(DEFS)

# Everything needed to use db.c
DBFILES= db.c compress.c player_list.c stringutil.c
DBOFILES= db.o compress.o player_list.o stringutil.o

# Everything except interface.c --- allows for multiple interfaces
CFILES= create.c game.c help.c look.c match.c move.c player.c predicates.c \
	rob.c set.c speech.c utils.c wiz.c game.c \
	boolexp.c unparse.c conc.c oldinterface.c $(DBFILES)

# .o versions of above
OFILES= create.o game.o help.o look.o match.o move.o player.o predicates.o \
	rob.o set.o speech.o utils.o wiz.o boolexp.o \
	unparse.o $(DBOFILES)

# Files in the standard distribution
DISTFILES= $(CFILES) config.h db.h externs.h interface.h match.h \
	interface.c sanity-check.c extract.c dump.c decompress.c \
	help.txt small.db minimal.db restart-cmu do_R)/decompress

# DO NOT REMOVE THIS LINE OR CHANGE ANYTHING AFTER IT #
boolexp.o: boolexp.c copyright.h db.h match.h externs.h config.h interface.h
compress.o: compress.c
create.o: create.c copyright.h db.h config.h interface.h externs.h
db.o: db.c copyright.h db.h config.h
decompress.o: decompress.c
dump.o: dump.c copyright.h db.h
extract.o: extract.c copyright.h db.h
fix.o: fix.c copyright.h db.h config.h
game.o: game.c copyright.h db.h config.h interface.h match.h externs.h
help.o: help.c copyright.h db.h config.h interface.h externs.h
interface.o: interface.c copyright.h db.h interface.h config.h
look.o: look.c copyright.h db.h config.h interface.h match.h externs.h
match.o: match.c copyright.h db.h config.h match.h
move.o: move.c copyright.h db.h config.h interface.h match.h externs.h
paths.o: paths.c copyright.h db.h config.h
player.o: player.c copyright.h db.h config.h interface.h externs.h
predicates.o: predicates.c copyright.h db.h interface.h config.h externs.h
rob.o: rob.c copyright.h db.h config.h interface.h match.h externs.h
sanity-check.o: sanity-check.c copyright.h db.h config.h
set.o: set.c copyright.h db.h config.h match.h interface.h externs.h
speech.o: speech.c copyright.h db.h interface.h match.h config.h externs.h
stringutil.o: stringutil.c copyright.h externs.h
unparse.o: unparse.c db.h externs.h config.h interface.h
utils.o: utils.c copyright.h db.h
wiz.o: wiz.c copyright.h db.h interface.h match.h externs.h
config.h: copyright.h
copyright.h:
db.h: copyright.h
externs.h: copyright.h db.h
interface.h: copyright.h db.h
match.h: copyright.h db.h
s.c wiz.c game.c \
	boolexp.c unparse.c conc.c oldinterface.c $(DBFILES)

# .o versions of above
OFILES= create.o game.o help.o look.o match.o move.o player.o predicates.o \
	rob.o set.o speech.o utils.o wiz.o boolexp.o \
	unparse.o $(DBOFILES)

# Files in the standard distribution
DISTFILES= $(CFILES) config.h db.h externs.h interface.h match.h \
	interface.c sanity-check.c extract.c dump.c decompress.c \
	help.txt small.db minimal.db restart-cmu do_copyright.h                                                                                            600    2471       0         2620  4634106555   6264                                                                                                                                                                                                                                                                                                                                                                      /* -*-C-*-

Copyright (c) 1989, 1990 by David Applegate, James Aspnes, Timothy Freeman,
		        and Bennet Yee.

This material was developed by the above-mentioned authors.
Permission to copy this software, to redistribute it, and to use it
for any purpose is granted, subject to the following restrictions and
understandings.

1. Any copy made of this software must include this copyright notice
in full.

2. Users of this software agree to make their best efforts (a) to
return to the above-mentioned authors any improvements or extensions
that they make, so that these may be included in future releases; and
(b) to inform the authors of noteworthy uses of this software.

3. All materials developed as a consequence of the use of this
software shall duly acknowledge such use, in accordance with the usual
standards of acknowledging credit in academic research.

4. The authors have made no warrantee or representation that the
operation of this software will be error-free, and the authors are
under no obligation to provide any services, by way of maintenance,
update, or o