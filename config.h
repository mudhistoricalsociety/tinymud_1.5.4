#include "copyright.h"

/* room number of player start location */
#define PLAYER_START ((dbref) 0)

/* minimum cost to create various things */
#define OBJECT_COST 10
#define EXIT_COST 1
#define LINK_COST 1
#define ROOM_COST 10

/* cost for various special commands */
#ifdef TINYHELL
# define FIND_COST 20
#else  TINYHELL
# define FIND_COST 100
#endif TINYHELL

#define PAGE_COST 1

/* limit on player name length */
#define PLAYER_NAME_LIMIT 16

/* magic cookies */
#define NOT_TOKEN '!'
#define AND_TOKEN '&'
#define OR_TOKEN '|'
#define THING_TOKEN 'x'
#define LOOKUP_TOKEN '*'
#define NUMBER_TOKEN '#'
#define ARG_DELIMITER '='

/* magic command cookies */
#define SAY_TOKEN '"'
#define POSE_TOKEN ':'

/* amount of object endowment, based on cost */
#define MAX_OBJECT_ENDOWMENT 100
#define OBJECT_ENDOWMENT(cost) (((cost)-5)/5)

/* amount at which temple stops being so profitable */
#define MAX_PENNIES 10000

/* penny generation parameters */
#define PENNY_RATE 10		/* 1/chance of getting a penny per room */

/* costs of kill command */
#define KILL_BASE_COST 100	/* prob = expenditure/KILL_BASE_COST */
#define KILL_MIN_COST 10
#define KILL_BONUS 50		/* paid to victim */

/* delimiter for lists of exit aliases */
#define EXIT_DELIMITER ';'

/* timing stuff */
#ifdef TINYHELL
# define DUMP_INTERVAL 21600	/* 6 hours (seconds) between dumps */
#else  TINYHELL
# define DUMP_INTERVAL 10800   /* 3 hours between dumps */
#endif TINYHELL

#define COMMAND_TIME_MSEC 100	/* time slice length in milliseconds */
#define COMMAND_BURST_SIZE 10	/* commands allowed per user in a burst */
#define COMMANDS_PER_TIME 1	/* commands per time slice after burst */

/* maximum amount of queued output */
#define MAX_OUTPUT 16384

#ifdef TINYHELL
/*---------------- TinyHELL Welcome, Registration messages ----------------*/
# define TINYPORT 6250
# define INTERNAL_PORT 6249
# define WELCOME_MESSAGE "Welcome to TinyHELL\nTo connect to your existing character, enter \"connect name password\"\nTo create a new character, enter \"create name password\"\nUse the news command to get up-to-date news on program changes.\n\nYou can disconnect using the QUIT command, which must be capitalized as shown.\n\nUse the WHO command to find out who is currently active.\n\n"
# define REGISTER_MESSAGE "In order to get an account, send mail to tinyhell-request@uokmax.ecn.uoknor.edu\nwith the following lines:\n\nPlayer: <playername>\nPassword: <password>\n\nYour character SHOULD be created in 72 hours.\n\n"
#endif TINYHELL

#ifdef ISLANDIA
/*---------------- Islandia Welcome, Registration messages ----------------*/
# define TINYPORT 2323
# define INTERNAL_PORT 2322
# define WELCOME_MESSAGE "Welcome to Islandia\nTo connect to your existing character, enter \"connect name password\"\nTo create a new character, enter \"create name password\"\nUse the news command to get up-to-date news on program changes.\n\nYou can disconnect using the QUIT command, which must be capitalized as shown.\n\nUse the WHO command to find out who is currently active.\n\n"
# define REGISTER_MESSAGE "You should not see this message\n\n"
#endif ISLANDIA

#ifndef TINYPORT
/*---------------- Generic Welcome, Registration messages ----------------*/
# define TINYPORT 4201
# define INTERNAL_PORT 4200
# define WELCOME_MESSAGE "Welcome to TinyMUD\nTo connect to your existing character, enter \"connect name password\"\nTo create a new character, enter \"create name password\"\nUse the news command to get up-to-date news on program changes.\n\nYou can disconnect using the QUIT command, which must be capitalized as shown.\n\nUse the WHO command to find out who is currently active.\n\n"
# define REGISTER_MESSAGE "You must send mail to the TinyMUD system administrator to get an account.\nUnfortunately, he or she forgot to set an Email address in this part of the\n code.  Good luck!\n\n"
#endif  TINYPORT

#define LEAVE_MESSAGE "\n***Disconnected***\n"

#define QUIT_COMMAND "QUIT"
#define WHO_COMMAND "WHO"
#define PREFIX_COMMAND "OUTPUTPREFIX"
#define SUFFIX_COMMAND "OUTPUTSUFFIX"

#ifdef ISLANDIA
# define HELP_FILE	"/clients/Islandia/lib/help.txt"
# define NEWS_FILE	"/clients/Islandia/lib/news.txt"
# define MOTD_FILE	"/clients/Islandia/lib/motd.txt"
# define CONNECT_FILE	"/clients/Islandia/lib/connect.txt"
# define WIZARD_FILE	"/clients/Islandia/lib/tinker.txt"
# define LOG_FILE	"/clients/Islandia/lib/islandia.log"
#endif ISLANDIA

#ifdef TINYHELL
# define HELP_FILE	"/usr/games/lib/tinyhell/help.txt"
# define NEWS_FILE	"/usr/games/lib/tinyhell/news.txt"
# define MOTD_FILE	"/usr/games/lib/tinyhell/motd.txt"
# define WIZARD_FILE	"/usr/games/lib/tinyhell/tinker.txt"
# define LOG_FILE	"/usr/games/lib/tinyhell/gnu.log"
#endif TINYHELL

#ifndef HELP_FILE
# define HELP_FILE	"help.txt"
# define NEWS_FILE	"news.txt"
# define MOTD_FILE	"motd.txt"
# define WIZARD_FILE	"wizard.txt"
# define LOG_FILE	"tinymud.log"
#endif HELP_FILE

#ifdef LOCKOUT
#define LOCKOUT_FILE "lockout.txt"
#endif /* LOCKOUT */

/*
 * This section defines the flag markers used by unparse.c
 * They are shipped so that they default to 1.5.3A without
 * the TINKER flag, and the Islandia settings with the
 * TINKER flag...of course, you can define them any way you
 * want, but then you may have to change other messages to
 * make the letters match their flag types.	--Fuzzy 5/31/90
 */

# define TYPE_CODES	"R-EP" /* Room, thing, exit, player */
# define STICKY_MARK	'S'
# define DARK_MARK	'D'
# define LINK_MARK	'L'
# define ABODE_MARK	'A'
# define HAVEN_MARK	'H'
# define UNWANTED_MARK	'U'
# define MALE_MARK	'M'
# define FEMALE_MARK	'F'
# define NEUTER_MARK	'N'

#ifndef TINKER
# define WIZARD_MARK	'W'  /* For Wizard */
# define TEMPLE_MARK	'T'  /* For Tinker */
# define ROBOT_MARK	'C'  /* For Cybernetic */
# define BUILDER_MARK	'B'  /* For Builder */
#else TINKER
# define WIZARD_MARK	'T'  /* For Tinker */
# define TEMPLE_MARK	'J'  /* For Junkpile */
# define ROBOT_MARK	'B'  /* For Bot */
# define BUILDER_MARK	'C'  /* For Constructor/Creator */
#endif TINKER
