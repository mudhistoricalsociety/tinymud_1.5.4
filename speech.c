#include "copyright.h"

/* Commands which involve speaking */

#include "db.h"
#include "interface.h"
#include "match.h"
#include "config.h"
#include "externs.h"

/* this function is a kludge for regenerating messages split by '=' */
const char *reconstruct_message(const char *arg1, const char *arg2)
{
    static char buf[BUFFER_LEN];

    if(arg2 && *arg2) {
	strcpy(buf, arg1);
	strcat(buf, " = ");
	strcat(buf, arg2);
	return buf;
    } else {
	return arg1;
    }
}

void do_say(dbref player, const char *arg1, const char *arg2)
{
    dbref loc;
    const char *message;
    char buf[BUFFER_LEN];

    if((loc = getloc(player)) == NOTHING) return;

    message = reconstruct_message(arg1, arg2);

    /* notify everybody */
    sprintf(buf, "You say \"%s\"", message);
    notify(player, buf);
    sprintf(buf, "%s says \"%s\"", db[player].name, message);
    notify_except(db[loc].contents, player, buf);
}

void do_whisper(dbref player, const char *arg1, const char *arg2)
{
#ifndef QUIET_WHISPER
    dbref loc;
#endif QUIET_WHISPER
    dbref who;
    char buf[BUFFER_LEN];
    char *det;
    int result;

    init_match(player, arg1, TYPE_PLAYER);
    match_neighbor();
    match_me();
    if(Wizard(player)) {
	match_absolute();
	match_player();
    }
    switch(who = match_result()) {
      case NOTHING:
	notify(player, "Whisper to whom?");
	break;
      case AMBIGUOUS:
	notify(player, "I don't know who you mean!");
	break;
      default:
        if (Typeof(who) == TYPE_PLAYER) {
	    sprintf(buf, "%s whispers \"%s\"", db[player].name, arg2);
	    if (notify(who, buf)) {
		sprintf(buf, "You whisper \"%s\" to %s.", arg2, db[who].name);
	        notify(player, buf);
#ifndef QUIET_WHISPER
		sprintf(buf, "%s whispers something to %s.",
			db[player].name, db[who].name);
		if((loc = getloc(player)) != NOTHING) {
		    notify_except2(db[loc].contents, player, who, buf);
		}
#endif /* QUIET_WHISPER */
	    }
	    else
		notify(player, "That person is not connected.");
	} else {
	    if (string_prefix (db[who].name, "a ") ||
	    	string_prefix (db[who].name, "an ") ||
	    	string_prefix (db[who].name, "the ") ||
	    	string_prefix (db[who].name, "some ")) {
		det = "";
	    } else if (lookup_player (db[who].name) != NOTHING) {
	       	det = "the thing called ";
    	    } else {
		det = "the ";
	    }
	    sprintf(buf, "You feel silly about whispering to %s%s.",
		    det, db[who].name);
	    notify(player, buf);
	}
	break;
    }
}

void do_pose(dbref player, const char *arg1, const char *arg2)
{
    dbref loc;
    const char *message;
    char buf[BUFFER_LEN];

    if((loc = getloc(player)) == NOTHING) return;

    message = reconstruct_message(arg1, arg2);

    /* notify everybody */
    sprintf(buf, "%s %s", db[player].name, message);
    notify_except(db[loc].contents, NOTHING, buf);
}

void do_wall(dbref player, const char *arg1, const char *arg2)
{
    dbref i;
    const char *message;
    char buf[512];

    message = reconstruct_message(arg1, arg2);
    if(Wizard(player)) {
	writelog("WALL from %s(%d): %s\n",
		db[player].name, player, message);
	sprintf(buf, "%s shouts \"%s\"", db[player].name, message);
	for(i = 0; i < db_top; i++) {
	    if(Typeof(i) == TYPE_PLAYER) {
		notify(i, buf);
	    }
	}
    } else {
	notify(player, "But what do you want to do with the wall?");
    }
}

void do_gripe(dbref player, const char *arg1, const char *arg2)
{
    dbref loc;
    const char *message;

    loc = db[player].location;
    message = reconstruct_message(arg1, arg2);
    writelog("GRIPE from %s(%d) in %s(%d): %s\n",
	    db[player].name, player,
	    db[loc].name, loc,
	    message);
    fflush(stderr);

#ifdef GOD_PRIV
    /* try telling GOD about it */
    if (!Flag(GOD,HAVEN)) {
	char buf[BUFFER_LEN];
	sprintf(buf, "%s gripes: \"%s\"",
		unparse_object(GOD, player), message);
	notify(GOD, buf);
    }
#endif GOD_PRIV    

    notify(player, "Your complaint has been duly noted.");
}

/* doesn't really belong here, but I couldn't figure out where else */
void do_page(dbref player, const char *arg1, const char *arg2)
{
    char buf[BUFFER_LEN];
    dbref target;
    int result;

    if(!payfor(player, PAGE_COST)) {
	notify(player, "You don't have enough pennies.");
    } else if((target = lookup_player(arg1)) == NOTHING) {
	notify(player, "I don't recognize that name.");
    } else if (db[target].flags & HAVEN) {
	notify(player, "That player is not accepting pages.");
    } else if (arg2 && *arg2) {
	sprintf(buf, "%s pages: %s", db[player].name, arg2);
	result = notify(target, buf);
	if (result) 
	    notify(player, "Your message has been sent.");
	else
	    notify(player, "That person is not connected.");
    } else {
	sprintf(buf, "You sense that %s is looking for you in %s.",
		db[player].name, db[db[player].location].name);
	result = notify(target, buf);
	if (result)
	    notify(player, "Your message has been sent.");
	else
	    notify(player, "That person is not connected.");
    }
}

void notify_except(dbref first, dbref exception, const char *msg)
{
    DOLIST (first, first) {
	if ((db[first].flags & TYPE_MASK) == TYPE_PLAYER
	    && first != exception) {
	    notify (first, msg);
	}
    }
}

void notify_except2(dbref first, dbref exc1, dbref exc2, const char *msg)
{
    DOLIST (first, first) {
	if ((db[first].flags & TYPE_MASK) == TYPE_PLAYER
	    && first != exc1
	    && first != exc2) {
	    notify (first, msg);
	}
    }
}
