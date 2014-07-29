/* ************************************************************************
*   File: db.h                                          Part of CircleMUD *
*  Usage: header file for database handling                               *
*                                                                         *
*  All rights reserved.  See license.doc for complete information.        *
*                                                                         *
*  Copyright (C) 1993, 94 by the Trustees of the Johns Hopkins University *
*  CircleMUD is based on DikuMUD, Copyright (C) 1990, 1991.               *
************************************************************************ */

/* arbitrary constants used by index_boot() (must be unique) */
#define DB_BOOT_WLD	0
#define DB_BOOT_MOB	1
#define DB_BOOT_OBJ	2
#define DB_BOOT_ZON	3
#define DB_BOOT_SHP	4

/* names of various files and directories */
#define TABLE_DIR   "table/"
#define CLAN_FILE 	"etc/clans"
#define CHAT_FILE       "world/chat.data"    /* for eliza chat stuff */
#define INDEX_FILE	"index"		/* index of world files		*/
#define MINDEX_FILE	"index.mini"	/* ... and for mini-mud-mode	*/
#define WLD_PREFIX	"world/wld"	/* room definitions		*/
#define MOB_PREFIX	"world/mob"	/* monster prototypes		*/
#define OBJ_PREFIX	"world/obj"	/* object prototypes		*/
#define ZON_PREFIX	"world/zon"	/* zon defs & command tables	*/
#define SHP_PREFIX	"world/shp"	/* shop definitions		*/
#define AREA_PREFIX	"world/area"	/* areas definitions		*/
#define MOB_DIR		"world/prg"	/* Mob programs			*/
#define PROG_DIR		"world/prg"	/* Mob programs			*/

#define CREDITS_FILE	"text/credits"	/* for the 'credits' command	*/
#define NEWS_FILE	"text/news"	/* for the 'news' command	*/
#define MOTD_FILE	"text/motd"	/* messages of the day / mortal	*/
#define IMOTD_FILE	"text/imotd"	/* messages of the day / immort	*/
#define HELP_KWRD_FILE	"text/help_table"/* for HELP <keywrd>		*/
#define HELP_KWRD_FILE_SKILLS	"text/help_skills"/* for HELP <keywrd>		*/
#define HELP_PAGE_FILE	"text/help"	/* for HELP <CR>		*/
#define INFO_FILE	"text/info"	/* for INFO			*/
#define WIZLIST_FILE	"text/wizlist"	/* for WIZLIST			*/
#define IMMLIST_FILE	"text/immlist"	/* for IMMLIST			*/
#define BACKGROUND_FILE	"text/background" /* for the background story	*/
#define POLICIES_FILE	"text/policies"	/* player policies/rules	*/
#define HANDBOOK_FILE	"text/handbook"	/* handbook for new immorts	*/
#define BUGLIST_FILE	"misc/bugs"	/* handbook for new immorts	*/
#define IDEALIST_FILE	"misc/ideas"	/* handbook for new immorts	*/
#define TYPOLIST_FILE	"misc/typos"	/* handbook for new immorts	*/

#define IDEA_FILE	"misc/ideas"	/* for the 'idea'-command	*/
#define TYPO_FILE	"misc/typos"	/*         'typo'		*/
#define BUG_FILE	"misc/bugs"	/*         'bug'		*/
#define MESS_FILE	"misc/messages"	/* damage messages		*/
#define SOCMESS_FILE	"misc/socials"	/* messgs for social acts	*/
#define XNAME_FILE	"misc/xnames"	/* invalid name substrings	*/
#define CHANNEL_FILE    "misc/channels" /* channel names                */

#define PLAYER_FILE	"etc/players"	/* the player database		*/
#define MAIL_FILE	"etc/plrmail"	/* for the mudmail system	*/
#define BAN_FILE	"etc/badsites"	/* for the siteban system	*/
#define HCONTROL_FILE	"etc/hcontrol"  /* for the house system		*/
#define MOBKILL_FILE	"etc/mobkills"  /* tracks mob kills		*/
#define TOPDAM_FILE	"etc/topdam"    /* tracks topdam		*/
#define TOPHURT_FILE	"etc/tophurt"   /* tracks tophurt		*/

#define PREF_FILE	"etc/pref"	  /* next pref number		*/
#define LAST_FILE	"etc/last"

/* public procedures in db.c */
void	boot_db(void);
int	create_entry(char *name);
void	zone_update(void);
int	real_room(int virtual);
char	*fread_string(FILE *fl, char *error);
long	get_id_by_name(char *name);
char	*get_name_by_id(long id);

void	char_to_store(struct char_data *ch, struct char_file_u *st);
void	store_to_char(struct char_file_u *st, struct char_data *ch);
int	load_char(char *name, struct char_file_u *char_element);
void	save_char(struct char_data *ch, sh_int load_room);
void	init_char(struct char_data *ch);
struct char_data* create_char(void);
struct char_data *read_mobile(int nr, int type, int zone);
int	real_mobile(int virtual);
int	vnum_mobile(char *searchname, struct char_data *ch);
void	clear_char(struct char_data *ch);
void	reset_char(struct char_data *ch);
void	free_char(struct char_data *ch);
void vwear_obj(int type, struct char_data * ch);
void vwear_object(int wearpos, struct char_data * ch);


struct obj_data *create_obj(void);
void	clear_object(struct obj_data *obj);
void	free_obj(struct obj_data *obj);
void    free_room(struct room_data *room);
int	real_object(int virtual);
struct obj_data *read_object(int nr, int type, int zone, int level);
int	vnum_object(char *searchname, struct char_data *ch);
int get_new_pref();

#define REAL 0
#define VIRTUAL 1

struct mob_kill_info {
    unsigned short int rnum, killed, pkills;
};

struct s_topdam {
    char ch[31], vict[31];
    int dam;
    int skill;
}  ;



/* structure for the reset commands */
struct reset_com {
    char	command;   /* current command                      */

    bool if_flag;	/* if TRUE: exe only if preceding exe'd */
    int	arg1;		/*                                      */
    int	arg2;		/* Arguments to the command             */
    int	arg3;		/*                                      */
    int line;		/* line number this command appears on  */

    /*
    *  Commands:              *
    *  'M': Read a mobile     *
    *  'O': Read an object    *
    *  'G': Give obj to mob   *
    *  'P': Put obj in obj    *
    *  'G': Obj to char       *
    *  'E': Obj to char equip *
    *  'D': Set state of door *
    */
};



/* zone definition structure. for the 'zone-table'   */
struct zone_data {
    char	*name;		    /* name of this zone                  */
    char *creator;	    /* name of creator			  */
    int  lvl_low;	    /* minimum level to enter zone        */
    int  lvl_high;  	    /* maximum level allowed in zone      */
    int	lifespan;           /* how long between resets (minutes)  */
    int	age;                /* current age of this zone (minutes) */
    int	top;                /* upper limit for rooms in this zone */
    int  num, sum, max, min, avg;  // number of mobs, max, min, avg levels of mobs
    int calc_ratio, def_ratio;
    char reset_msg[100];

    int	reset_mode;         /* conditions for reset (see below)   */
    int	number;		    /* virtual number of this zone	  */
    struct reset_com *cmd;   /* command table for reset	          */
    char disk_name[100]; // name of the zone on the hard disk, needed for whole zone in one file support

    /*
    *  Reset mode:                              *
    *  0: Don't reset, and don't update age.    *
    *  1: Reset if no PC's are located in zone. *
    *  2: Just reset.                           *
    */
};



/* for queueing zones for update   */
struct reset_q_element {
    int	zone_to_reset;            /* ref to zone_data */
    struct reset_q_element *next;
};



/* structure for the update queue     */
struct reset_q_type {
    struct reset_q_element *head;
    struct reset_q_element *tail;
};



struct player_index_element {
    char	*name;
    long id;
};


struct help_index_element {
    char	*keyword;
    long	pos;
};

/* don't change these */
#define BAN_NOT 	0
#define BAN_NEW 	1
#define BAN_SELECT	2
#define BAN_ALL		3

#define BANNED_SITE_LENGTH    50
struct ban_list_element {
    char	site[BANNED_SITE_LENGTH+1];
    int	type;
    time_t date;
    char	name[MAX_NAME_LENGTH+1];
    struct ban_list_element *next;
};


/* global buffering system */

#ifdef __DB_C__
char	buf[MAX_STRING_LENGTH];
char	buf1[MAX_STRING_LENGTH];
char	buf2[MAX_STRING_LENGTH];
char	arg[MAX_STRING_LENGTH];
#else
extern char	buf[MAX_STRING_LENGTH];
extern char	buf1[MAX_STRING_LENGTH];
extern char	buf2[MAX_STRING_LENGTH];
extern char	arg[MAX_STRING_LENGTH];
#endif

#ifndef __CONFIG_C__
extern char	*OK;
extern char	*NOPERSON;
extern char	*NOEFFECT;
#endif
