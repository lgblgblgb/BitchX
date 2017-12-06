/*
 * Module/dll handling code written by Colten Edwards.
 * Copyright 1997
 */
#ifndef MODULE_H_
#define MODULE_H_


/*
 * if we change the table below, we change this module number to the 
 * current date (YYYYMMDDxx where xx is a serial number).
 */
#define MODULE_VERSION 2017120601UL

#include "struct.h"

typedef int (*Function_ptr)();

#ifdef WANT_DLL
#ifdef HPUX
#include <dl.h>
#endif

#define COMMAND_PROC	0x0001		/* New /command proc return void */
#define ALIAS_PROC	0x0002		/* new $alias proc return new_malloc'd string */
#define CTCP_PROC	0x0004		/* new ctcp proc return new_malloc'd string*/
#define VAR_PROC	0x0008		/* new variable no return */
#define HOOK_PROC	0x0010		/* new numeric proc 
					 * return int 1 if we don't want client
					 * to also handle this.
					 * or 0  if we want client to handle
					 */
#define RAW_PROC	0x0020		/* new raw irc proc */
#define DCC_PROC	0x0040		/* add to dcc command list */
#define OUTPUT_PROC	0x0080		/* New output proc for all windows. */
#define WINDOW_PROC	0x0100		/* New window proc */
#define TABLE_PROC	0x8000		/* removing a global_table proc */

#define INVALID_MODVERSION -1

typedef int (Irc_PackageInitProc)  (IrcCommandDll **, Function_ptr *);
typedef char *(Irc_PackageVersionProc)  (IrcCommandDll **);

typedef struct _function_table 
{
	char	*name;
	char	*desc;
	int	id;
	int	flag;
	void	*func1;
	void	*func2;
} Function;

typedef struct _package_installed {
	struct _package_installed *next;
	char    *name;
	char    *version;

	int	major;
	int	minor;
	int	lock;

#if defined(HPUX)
	shl_t handle;
#elif defined(__EMX__)
	HMODULE handle;
#elif defined(WINNT)
	HINSTANCE handle;
#else
	void	*handle;
#endif
	Irc_PackageInitProc *cleanup;
} Packages;
                                
Packages *find_module (char *);
int BX_add_module_proc (unsigned int, char *, char *, char *, int, int, void *, void *);
int remove_package (char *);
int BX_remove_module_proc (unsigned int, char *, char *, char *);
int add_module(unsigned int, Function *, char *);

extern BuiltInDllFunctions *dll_functions;
#ifndef __hook_c
extern NumericFunction *dll_numeric_list;
#endif
extern IrcCommandDll *dll_commands;
extern CtcpEntryDll *dll_ctcp;
extern WindowDll *dll_window;
extern IrcVariableDll *dll_variable;

IrcCommandDll *find_dll_command(const char *, int *);
char *BX_get_dllstring_var(char *);
int BX_get_dllint_var(char *);
void BX_set_dllstring_var(char *, char *);
void BX_set_dllint_var(char *, unsigned int);
void BX_save_dllvar(FILE *, char *);
RawDll *find_raw_proc(char *, char **);

int check_version(unsigned long);
#endif /* WANT_DLL */

/* 
 * the order of this enum is extremely important. ie a module compiled
 * on a differant order would fail miserably. So when adding to the list
 * make sure and add to the end of the list.
 */
 
enum FUNCTION_VALUE
{
/* ircaux.c */
	MODULE_VERSION_CHECK,
/* output.c */	
	PUT_IT,
	BITCHSAY,
	YELL,
	ADD_TO_LOG,
	VSNPRINTF,
	SNPRINTF,
	NEW_MALLOC,
	NEW_FREE,
	NEW_REALLOC,
	MALLOC_STRCPY,
	MALLOC_STRCAT,
	MALLOC_STR2CPY,
	M_3DUP,
	M_OPENDUP,
	M_S3CAT,
	M_S3CAT_S,
	M_3CAT,
	UPPER,
	LOWER,
	STRISTR,
	RSTRISTR,
	WORD_COUNT,
	REMOVE_TRAILING_SPACES,
	MY_STRICMP,
	MY_STRNICMP,
	MY_STRNSTR,
	CHOP,
	STRMCPY,
	STRMCAT,
	SCANSTR,
	EXPAND_TWIDDLE,
	CHECK_NICKNAME,
	SINDEX,
	RSINDEX,
	ISNUMBER,
	RFGETS,
	PATH_SEARCH,
	DOUBLE_QUOTE,
	IRCPANIC,
	END_STRCMP,
	BEEP_EM,
	UZFOPEN,
	FUNC_GET_TIME,
	TIME_DIFF,
	TIME_TO_NEXT_MINUTE,
	PLURAL,
	MY_CTIME,
	LTOA,
	STRFORMAT,
	MATCHINGBRACKET,
	PARSE_NUMBER,
	SPLITW,
	UNSPLITW,
	M_2DUP,
	M_E3CAT,
	CHECK_VAL,
	ON_OFF,
	STREXTEND,
	STRFILL,
	EMPTY_FUNC,
	REMOVE_BRACKETS,
	MY_ATOL,
	M_DUPCHAR,
	STREQ,
	STRIEQ,
	STRMOPENCAT,
	OV_STRCPY,
	STRIP_CONTROL,
	FIGURE_OUT_ADDRESS,
	STRNRCHR,
	MASK_DIGITS,
	CCSPAN,
	CHARCOUNT,
	STRPCAT,
	STRCPY_NOCOLORCODES,
	CRYPTIT,
	STRIPDEV,
	MANGLE_LINE,
	M_STRDUP,
	M_STRCAT_UES,
	M_STRNDUP,
	MALLOC_SPRINTF,
	M_SPRINTF,
	NEXT_ARG,
	NEW_NEXT_ARG,
	NEW_NEW_NEXT_ARG,
	LAST_ARG,
	NEXT_IN_COMMA_LIST,
	RANDOM_NUMBER,
	
/* words.c */
	STRSEARCH,
	MOVE_TO_WORD,
	MOVE_WORD_REL,
	EXTRACT,
	EXTRACT2,
	WILD_MATCH,
/* network */
	CONNECT_BY_NUMBER,
	RESOLV,
	LOOKUP_HOST,
	LOOKUP_IP,
	HOST_TO_IP,
	IP_TO_HOST,
	ONE_TO_ANOTHER,
	SET_BLOCKING,
	SET_NON_BLOCKING,

/* list.c */
	ADD_TO_LIST,
	ADD_TO_LIST_EXT,
	REMOVE_FROM_LIST_,
	REMOVE_FROM_LIST_EXT,
	REMOVEWILD_FROM_LIST,
	LIST_LOOKUP,
	LIST_LOOKUP_EXT,
	FIND_IN_LIST,
	FIND_IN_LIST_EXT,
/* alist.c */
	ADD_TO_ARRAY,
	REMOVE_FROM_ARRAY,
	ARRAY_POP,
	REMOVE_ALL_FROM_ARRAY,
	ARRAY_LOOKUP,
	FIND_ARRAY_ITEM,
	FIND_FIXED_ARRAY_ITEM,
	
/* server.c */
	SEND_TO_SERVER,
	QUEUE_SEND_TO_SERVER,
	MY_SEND_TO_SERVER,
/* connecting to the server */
	GET_CONNECTED,
	CONNECT_TO_SERVER_BY_REFNUM,
	CLOSE_SERVER,
	IS_SERVER_CONNECTED,
	FLUSH_SERVER,
	SERVER_IS_CONNECTED,
	IS_SERVER_OPEN,
	CLOSE_ALL_SERVER,
/* server file reading */
	READ_SERVER_FILE,
	ADD_TO_SERVER_LIST,
	BUILD_SERVER_LIST,
	DISPLAY_SERVER_LIST,
	PARSE_SERVER_INFO,
	SERVER_LIST_SIZE,
/* misc server/nickname functions */
	FIND_SERVER_REFNUM,
	FIND_IN_SERVER_LIST,
	PARSE_SERVER_INDEX,
	SET_SERVER_REDIRECT,
	GET_SERVER_REDIRECT,
	CHECK_SERVER_REDIRECT,
	FUDGE_NICKNAME,
	RESET_NICKNAME,
/* various set server struct functions */
	SET_SERVER_COOKIE,
	UPDATE_SERVER_UMODE,
	SET_SERVER_MOTD,
	SET_SERVER_OPERATOR,
	SET_SERVER_ITSNAME,
	SET_SERVER_VERSION,
	SET_SERVER_LAG,
	SET_SERVER_PASSWORD,
	SET_SERVER_NICKNAME,
	SET_SERVER2_8,
	SET_SERVER_AWAY,
/* various get server struct functions */
	GET_SERVER_COOKIE,
	GET_SERVER_NICKNAME,
	GET_SERVER_NAME,
	GET_SERVER_ITSNAME,
	GET_SERVER_MOTD,
	GET_SERVER_OPERATOR,
	GET_SERVER_VERSION,
	GET_SERVER_FLAG,
	GET_SERVER_PORT,
	GET_SERVER_LAG,
	GET_SERVER2_8,
	GET_UMODE,
	GET_SERVER_AWAY,
	GET_SERVER_NETWORK,
	GET_PENDING_NICKNAME,
	SERVER_DISCONNECT,

	GET_SERVER_LIST,
	GET_SERVER_CHANNELS,

	SET_SERVER_LAST_CTCP_TIME,
	GET_SERVER_LAST_CTCP_TIME,
	SET_SERVER_TRACE_FLAG,
	GET_SERVER_TRACE_FLAG,
	GET_SERVER_READ,
	GET_SERVER_LINKLOOK,
	SET_SERVER_LINKLOOK,
	GET_SERVER_LINKLOOK_TIME,
	SET_SERVER_LINKLOOK_TIME,
	GET_SERVER_TRACE_KILL,
	SET_SERVER_TRACE_KILL,
	ADD_SERVER_CHANNELS,
	SET_SERVER_CHANNELS,
	SEND_MSG_TO_CHANNELS,
	SEND_MSG_TO_NICKS,
	IS_SERVER_QUEUE,
/* glob.c */
	BSD_GLOB,
	BSD_GLOBFREE,			
	
	CONVERT_OUTPUT_FORMAT,
	UPDATE_CLOCK,
	BREAKARGS,
	PASTEARGS,
	USERAGE,
	SEND_TEXT,
	SET_LASTLOG_MSG_LEVEL,
	SPLIT_CTCP,
	RANDOM_STR,
	DCC_PRINTF,

	MY_ENCRYPT,
	MY_DECRYPT,
	PREPARE_COMMAND,
	BUILD_STATUS,
	FUNC_LOAD,

	HOOK,
/* irc.c */
	IRC_IO_FUNC,
	IRC_EXIT_FUNC,
/* alias.c */
	LOCK_STACK_FRAME,
	UNLOCK_STACK_FRAME,
	
	
/* input.c */
	FUNC_UPDATE_INPUT,
	CURSOR_TO_INPUT,
	SET_INPUT,
	GET_INPUT,
	SET_INPUT_PROMPT,
	GET_INPUT_PROMPT,
	ADDTABKEY,
	GETTABKEY,
	GETNEXTNICK,
	GETCHANNICK,
	LOOKUP_NICKCOMPLETION,
	ADD_COMPLETION_TYPE,
		
/* module.c */
	ADD_MODULE_PROC,
	REMOVE_MODULE_PROC,
/* names.c */	
	IS_CHANOP,
	IS_CHANNEL,
	MAKE_CHANNEL,
	IM_ON_CHANNEL,
	IS_ON_CHANNEL,
	ADD_CHANNEL,
	ADD_TO_CHANNEL,
	GET_CHANNEL_KEY,
	FUNC_RECREATE_MODE,
	FUNC_COMPRESS_MODES,
	FUNC_GOT_OPS,
	GET_CHANNEL_BANS,
	GET_CHANNEL_MODE,
	CLEAR_BANS,
	REMOVE_CHANNEL,
	REMOVE_FROM_CHANNEL,
	RENAME_NICK,
	GET_CHANNEL_OPER,
	GET_CHANNEL_HALFOP,
	FETCH_USERHOST,
	GET_CHANNEL_VOICE,
	CREATE_CHANNEL_LIST,
	FLUSH_CHANNEL_STATS,
	LOOKUP_CHANNEL,
		
	FIND_NICKLIST_IN_CHANNELLIST,
	ADD_NICKLIST_TO_CHANNELLIST,
	NEXT_NICKLIST,

	NEXT_NAMELIST,
	ADD_NAME_TO_GENERICLIST,
	FIND_NAME_IN_GENERICLIST,
	ADD_WHOWAS_USERHOST_CHANNEL,
	FIND_USERHOST_CHANNEL,
	NEXT_USERHOST,
	SORTED_NICKLIST,
	CLEAR_SORTED_NICKLIST,
	ADD_NAME_TO_FLOODLIST,
	FIND_NAME_IN_FLOODLIST,
	CLEAR_WHOWAS_HASH_TABLE,
	REMOVE_OLDEST_WHOWAS_HASHLIST,
	
		
/* cset.c fset.c vars.c */	
	FGET_STRING_VAR,
	FSET_STRING_VAR,
	GET_WSET_STRING_VAR,
	SET_WSET_STRING_VAR,
	SET_CSET_INT_VAR,
	GET_CSET_INT_VAR,
	SET_CSET_STR_VAR,
	GET_CSET_STR_VAR,
	GET_DLLINT_VAR,
	SET_DLLINT_VAR,
	GET_DLLSTRING_VAR,
	SET_DLLSTRING_VAR,
	SAVE_DLLVAR,
	GET_INT_VAR,
	SET_INT_VAR,
	GET_STRING_VAR,
	SET_STRING_VAR,

	ADD_TIMER,
	DELETE_TIMER,
	DELETE_ALL_TIMERS,

/* sockets from misc.c */
	ADD_SOCKETREAD,
	ADD_SOCKETTIMEOUT,
	CLOSE_SOCKETREAD,
	GET_SOCKET,
	SET_SOCKETFLAGS,
	GET_SOCKETFLAGS,
	GET_SOCKETINFO,
	SET_SOCKETINFO,
	SET_SOCKETWRITE,
	CHECK_SOCKET,
	READ_SOCKETS,
	WRITE_SOCKETS,
	GET_MAX_FD,
	NEW_CLOSE,
	NEW_OPEN,	
	DGETS,


/* screen.c */
	PREPARE_DISPLAY,
	ADD_TO_WINDOW,
	SKIP_INCOMING_MIRC,
	ADD_TO_SCREEN,
	SPLIT_UP_LINE,
	OUTPUT_LINE,
	OUTPUT_WITH_COUNT,
	SCROLL_WINDOW,
	CURSOR_NOT_IN_DISPLAY,
	CURSOR_IN_DISPLAY,
	IS_CURSOR_IN_DISPLAY,
	REPAINT_WINDOW,
	CREATE_NEW_SCREEN,
	CREATE_ADDITIONAL_SCREEN,
	KILL_SCREEN,
	XTERM_SETTITLE,
	ADD_WAIT_PROMPT,
	SKIP_CTL_C_SEQ,
	STRIP_ANSI,

/* window.c */
	FREE_FORMATS,
	REMOVE_WINDOW_FROM_SCREEN,
	SET_SCREENS_CURRENT_WINDOW,
	NEW_WINDOW,
	DELETE_WINDOW,
	TRAVERSE_ALL_WINDOWS,
	ADD_TO_INVISIBLE_LIST,
	ADD_TO_WINDOW_LIST,
	RECALCULATE_WINDOW_POSITIONS,
	MOVE_WINDOW,
	RESIZE_WINDOW,
	REDRAW_ALL_WINDOWS,
	REBALANCE_WINDOWS,
	RECALCULATE_WINDOWS,
	UPDATE_ALL_WINDOWS,
	GOTO_WINDOW,
	HIDE_BX_WINDOW,
	FUNC_SWAP_LAST_WINDOW,
	FUNC_SWAP_NEXT_WINDOW,
	FUNC_SWAP_PREVIOUS_WINDOW,
	SHOW_WINDOW,
	GET_STATUS_BY_REFNUM,
	GET_WINDOW_BY_DESC,
	GET_WINDOW_BY_REFNUM,
	GET_VISIBLE_BY_REFNUM,
	GET_WINDOW_BY_NAME,
	FUNC_NEXT_WINDOW,
	FUNC_PREVIOUS_WINDOW,
	UPDATE_WINDOW_STATUS,
	UPDATE_ALL_STATUS,
	UPDATE_WINDOW_STATUS_ALL,
	STATUS_UPDATE,
	SET_PROMPT_BY_REFNUM,
	GET_PROMPT_BY_REFNUM,
	QUERY_NICK, /* DEFUNCT */
	QUERY_HOST, /* DEFUNCT */
	QUERY_CMD, /* DEFUNCT */
	GET_TARGET_BY_REFNUM,
	GET_TARGET_CMD_BY_REFNUM,
	GET_WINDOW_TARGET_BY_DESC,
	IS_CURRENT_CHANNEL,
	SET_CURRENT_CHANNEL_BY_REFNUM,
	GET_CURRENT_CHANNEL_BY_REFNUM,
	GET_REFNUM_BY_WINDOW,
	IS_BOUND_TO_WINDOW,
	GET_WINDOW_BOUND_CHANNEL,
	IS_BOUND_ANYWHERE,
	IS_BOUND,
	UNBIND_CHANNEL,
	GET_BOUND_CHANNEL,
	GET_WINDOW_SERVER,
	SET_WINDOW_SERVER,
	WINDOW_CHECK_SERVERS,
	CHANGE_WINDOW_SERVER,
	SET_LEVEL_BY_REFNUM,
	SET_SERVER_STAT_FLAG,
	GET_SERVER_STAT_FLAG,
	MESSAGE_TO,
	CLEAR_WINDOW,
	CLEAR_ALL_WINDOWS,
	CLEAR_WINDOW_BY_REFNUM,
	UNCLEAR_WINDOW_BY_REFNUM,
	SET_SCROLL_LINES,
	SET_CONTINUED_LINES,
	CURRENT_REFNUM,
	NUMBER_OF_WINDOWS_ON_SCREEN,
	SET_SCROLLBACK_SIZE,
	IS_WINDOW_NAME_UNIQUE,
	GET_NICKLIST_BY_WINDOW,
	SCROLLBACK_BACKWARDS_LINES,
	SCROLLBACK_FORWARDS_LINES,
	SCROLLBACK_FORWARDS,
	SCROLLBACK_BACKWARDS,
	SCROLLBACK_END,
	SCROLLBACK_START,
	SET_HOLD_MODE,
	UNHOLD_WINDOWS,
	FUNC_UNSTOP_ALL_WINDOWS,
	RESET_LINE_CNT,
	FUNC_TOGGLE_STOP_SCREEN,
	FLUSH_EVERYTHING_BEING_HELD,
	UNHOLD_A_WINDOW,
	RECALCULATE_WINDOW_CURSOR,
	MAKE_WINDOW_CURRENT,
	CLEAR_SCROLLBACK,
	SET_DISPLAY_TARGET,
	RESET_DISPLAY_TARGET,
	RESTORE_DISPLAY_TARGET,
	SAVE_DISPLAY_TARGET,
	
	IS_OTHER_FLOOD,
	CHECK_FLOODING,
	FLOOD_PROT,	
/* expr.c */
	
	NEXT_UNIT,
	EXPAND_ALIAS,
	PARSE_INLINE,
	ALIAS_SPECIAL_CHAR,
	PARSE_LINE,
	PARSE_COMMAND_FUNC,
	MAKE_LOCAL_STACK,
	DESTROY_LOCAL_STACK,
	
/* dcc.c */
	DCC_CREATE_FUNC,
	FIND_DCC_FUNC,
	ERASE_DCC_INFO,	
	ADD_DCC_BIND,
	REMOVE_DCC_BIND,
	REMOVE_ALL_DCC_BINDS,
	GET_ACTIVE_COUNT,
	GET_NUM_QUEUE,
	ADD_TO_QUEUE,
	DCC_FILESEND,
	DCC_RESEND,
		
/* who.c */
	WHOBASE,
	ISONBASE,
	USERHOSTBASE,

	FIND_COMMAND_FUNC,
			

	NICKNAME,
	IRC_VERSION,
	FROM_SERVER,
	CONNECTED_TO_SERVER,
	PRIMARY_SERVER,
	PARSING_SERVER_INDEX,
	NOW,
	START_TIME,
	IDLE_TIME,

	LOADING_GLOBAL,
	TARGET_WINDOW,
	CURRENT_WINDOW,
	INVISIBLE_LIST,
	
	MAIN_SCREEN,
	LAST_INPUT_SCREEN,
	OUTPUT_SCREEN,
	SCREEN_LIST,
	IRCLOG_FP,
	DOING_NOTICE,

	WINDOW_DISPLAY,
	STATUS_UPDATE_FLAG,
	TABKEY_ARRAY,
	AUTOREPLY_ARRAY,
	IDENTD_SOCKET,
				
	VAR_TCL_INTERP,
        LASTCLICKLINEDATA,
        CONTEXTX,
        CONTEXTY,
        GUIIPC,
	GUI_MUTEX_LOCK,
	GUI_MUTEX_UNLOCK,
	
/* input output functions */
	SERV_OPEN_FUNC,
	SERV_INPUT_FUNC,
	SERV_OUTPUT_FUNC,
	SERV_CLOSE_FUNC,
	CHECK_EXT_MAIL_STATUS,
	CHECK_EXT_MAIL,
	DEFAULT_OUTPUT_FUNCTION,
	DEFAULT_STATUS_OUTPUT_FUNCTION,

/* names.c */
    IS_HALFOP,

/* leave at the end */
	NUMBER_OF_GLOBAL_FUNCTIONS
};

extern Function_ptr global_table[];
extern IrcCommand irc_command[];

#endif
