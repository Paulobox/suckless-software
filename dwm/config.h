/* See LICENSE file for copyright and license details. */

/* Constants */
#define BROWSER "firefox"
#define TERMINAL "st"
#define TERMCLASS "St"

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 2;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 1;       /* vert inner gap between windows */
static const unsigned int gappoh    = 3;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 4;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const Bool viewontag         = True;     /* Switch view on tag switch */
static const char *fonts[]          = { "Hack Nerd Font Mono:size=11", "NotoColorEmoji:pixelsize=10:antialias=true:autohint=true"  };
static const char dmenufont[]       = "monospace:size=10";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#393939";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

static const char *const autostart[] = {
	"slstatus", NULL,
	"st", NULL,
  "xcompmgr", NULL,
  "unclutter", NULL,
  "shufwall", NULL,
  "scroll", NULL,
  "xsetupdaterate", NULL,
	NULL /* terminate */
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {TERMINAL, "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {TERMINAL, "-n", "spcalc", "-f", "monospace:size=16", "-g", "50x20", "-e", "bc", "-lq", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spcalc",      spcmd2},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
  /* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
  { "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
  /* { "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 }, */
  { NULL,      NULL,     "Event Tester", 0,         0,          0,         1,        -1 }, /* xev */
  { TERMCLASS,  NULL,       NULL,        0,         0,          1,         0,        -1 },
	{ TERMCLASS,  "floatterm", NULL,       0,         1,          1,         0,        -1 },
	{ TERMCLASS,  "bg",        NULL,       1 << 7,    0,          1,         0,        -1 },
	{ TERMCLASS,  "spterm",    NULL,       SPTAG(0),  1,          1,         0,        -1 },
	{ TERMCLASS,  "spcalc",    NULL,       SPTAG(1),  1,          1,         0,        -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *termcmd2[]  = { "kitty", NULL };
static const char *power_menu[] = { "rofi", "-show", "power-menu", "-modi", "power-menu:~/.local/bin/rofi-power-menu", NULL };

#include "toggleborders.c"
#include "shiftview.c"
#include "movestack.c"
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ControlMask,           XK_t, spawn,          {.v = termcmd2 } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
  { MODKEY|ControlMask,             XK_b,      toggleborder,     {0} },
  { MODKEY|ShiftMask,                XK_b,      toggleallborders, {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,		        	          XK_i,		incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,	          	XK_i,		incnmaster,     {.i = -1 } },
  { MODKEY|ShiftMask,		          XK_Return,	    togglescratch,	{.ui = 0} },
  { MODKEY,			                  XK_apostrophe,	togglescratch,	{.ui = 1} },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	/* Vanity GAPS + cfact combo START */
  { MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
  { MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
  { MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
  { MODKEY,                       XK_equal,  incrgaps,       {.i = +3 } },
  { MODKEY,                       XK_minus,  incrgaps,       {.i = -3 } },
  { MODKEY,                       XK_z,      incrgaps,       {.i = +3 } },
  { MODKEY,                       XK_x,      incrgaps,       {.i = -3 } },
  { MODKEY|Mod4Mask,              XK_i,      incrigaps,      {.i = +1 } },
  { MODKEY|Mod4Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
  { MODKEY|Mod4Mask,              XK_o,      incrogaps,      {.i = +1 } },
  { MODKEY|Mod4Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
  { MODKEY|Mod4Mask,              XK_6,      incrihgaps,     {.i = +1 } },
  { MODKEY|Mod4Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
  { MODKEY|Mod4Mask,              XK_7,      incrivgaps,     {.i = +1 } },
  { MODKEY|Mod4Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
  { MODKEY|Mod4Mask,              XK_8,      incrohgaps,     {.i = +1 } },
  { MODKEY|Mod4Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
  { MODKEY|Mod4Mask,              XK_9,      incrovgaps,     {.i = +1 } },
  { MODKEY|Mod4Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
  { Mod4Mask|ShiftMask,           XK_a,      togglegaps,     {0} },
  { MODKEY|ShiftMask,             XK_a,      defaultgaps,    {0} },
	/* combo END */
	{ Mod4Mask,                     XK_g,      shiftview,      {.i = +1 } },
	{ Mod4Mask|ShiftMask,           XK_g,      shiftview,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY|ControlMask,           XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,	                  		XK_q,	     killclient,	   {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ Mod4Mask,                     XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_F5,     xrdb,           {.v = NULL } },
  /* custom (commands)  */
  { MODKEY|ShiftMask,             XK_q,      spawn,          {.v = power_menu } },
  { MODKEY|ShiftMask,		XK_BackSpace,	spawn,		{.v = (const char*[]){ "dmenuexit", NULL } } },
  { MODKEY|ShiftMask,   XK_e,         spawn,		{.v = (const char*[]){ "dmenuemoji", NULL } } },
  { MODKEY|ShiftMask,   XK_t,         spawn,		{.v = (const char*[]){ "dmenuconfigedit", NULL } } },
  /* { MODKEY,             XK_j,         spawn,		{.v = (const char*[]){ "dmenudirjump", NULL } } }, */
  { MODKEY,             XK_Print,     spawn,    {.v = (const char*[]) { "flameshot", "gui", NULL } } },
  { MODKEY|ShiftMask,   XK_r,         spawn,    {.v = (const char*[]) { "rofi", "-show", "drun", NULL } } },
	{ MODKEY,			XK_w,		spawn,		{.v = (const char*[]){ BROWSER, NULL } } },
  /* brightness and audio */
  { 0,                            0x1008ff02,    spawn,                  SHCMD ("light -A 5")},
	{ 0,                            0x1008ff03,    spawn,                  SHCMD ("light -U 5")},
	{ 0,                            0x1008ff11,    spawn,                  SHCMD ("amixer sset Master 5%- unmute")},
	{ 0,                            0x1008ff12,    spawn,                  SHCMD ("amixer sset Master $(amixer get Master | grep -q '\\[on\\]' && echo 'mute' || echo 'unmute')")},
	{ 0,                            0x1008ff13,    spawn,                  SHCMD ("amixer sset Master 5%+ unmute")},
  /* move windows */
	{ Mod4Mask,                       XK_Down,   moveresize,     {.v = "0x 25y 0w 0h" } },
	{ Mod4Mask,                       XK_Up,     moveresize,     {.v = "0x -25y 0w 0h" } },
	{ Mod4Mask,                       XK_Right,  moveresize,     {.v = "25x 0y 0w 0h" } },
	{ Mod4Mask,                       XK_Left,   moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ Mod4Mask|ShiftMask,             XK_Down,   moveresize,     {.v = "0x 0y 0w 25h" } },
	{ Mod4Mask|ShiftMask,             XK_Up,     moveresize,     {.v = "0x 0y 0w -25h" } },
	{ Mod4Mask|ShiftMask,             XK_Right,  moveresize,     {.v = "0x 0y 25w 0h" } },
	{ Mod4Mask|ShiftMask,             XK_Left,   moveresize,     {.v = "0x 0y -25w 0h" } },
  /* move to edge */
{ Mod4Mask|ControlMask,           XK_Up,     moveresizeedge, {.v = "t"} },
{ Mod4Mask|ControlMask,           XK_Down,   moveresizeedge, {.v = "b"} },
{ Mod4Mask|ControlMask,           XK_Left,   moveresizeedge, {.v = "l"} },
{ Mod4Mask|ControlMask,           XK_Right,  moveresizeedge, {.v = "r"} },
{ Mod4Mask|ControlMask|ShiftMask, XK_Up,     moveresizeedge, {.v = "T"} },
{ Mod4Mask|ControlMask|ShiftMask, XK_Down,   moveresizeedge, {.v = "B"} },
{ Mod4Mask|ControlMask|ShiftMask, XK_Left,   moveresizeedge, {.v = "L"} },
{ Mod4Mask|ControlMask|ShiftMask, XK_Right,  moveresizeedge, {.v = "R"} },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
  { MODKEY|ShiftMask,             XK_Escape, quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        moveorplace,    {.i = 1} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

