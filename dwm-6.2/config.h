/* See LICENSE file for copyright and license details. */
#define XF86AudioPrev           0x1008ff16
#define XF86AudioPlay           0x1008ff14
#define XF86AudioNext           0x1008ff17
#define XF86AudioMute           0x1008ff12
#define XF86AudioLowerVolume    0x1008ff11
#define XF86AudioRaiseVolume    0x1008ff13
/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int gappx     = 10;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

/*   Display modes of the tab bar: never shown, always shown, shown only in */
/*   monocle mode in presence of several windows.                           */
/*   Modes after showtab_nmodes are disabled                                */
enum showtab_modes { showtab_never, showtab_auto, showtab_nmodes, showtab_always};
static const int showtab            = showtab_auto; /* Default tab bar show mode */
static const int toptab             = True;    /* False means bottom tab bar */

static const char *fonts[]          = { "xos4 Terminus:size=9", "TerminessTTF Nerd Font:size=9" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#000000";
static const char col_cyan[]        = "#076678";

/* solarized colors http://ethanschoonover.com/solarized */
static const char s_base03[]        = "#002b36";
static const char s_base02[]        = "#073642";
static const char s_base01[]        = "#586e75";
static const char s_base00[]        = "#657b83";
static const char s_base0[]         = "#839496";
static const char s_base1[]         = "#93a1a1";
static const char s_base2[]         = "#eee8d5";
static const char s_base3[]         = "#fdf6e3";


static const char *colors[][3]      = {
	/*               fg         bg         border   */
	{ s_base0, s_base03, s_base2 },      /* SchemeNorm dark */
	{ col_gray4, col_cyan,  col_cyan  }, /* SchemeSel dark */
	{ s_base00, s_base3, s_base02 },     /* SchemeNorm light */
	{ s_base00, s_base2, s_base02},      /* SchemeSel light */
	{ col_gray3, col_gray1, col_gray2 }, /* SchemeNorm orig */
	{ col_gray4, col_cyan,  col_cyan  }, /* SchemeSel orig */
};

/* tagging */
static const char *tags[] = { "" , "" , "", "", "", "", " ", " ", " " };
static const char *tagsalt[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   isterminal noswallow monitor */
	{ "Gimp",     NULL,       NULL,       1 << 6,            1,     0, 0,      -1 },
	{ "firefox",  NULL,       NULL,       1 << 1,       0,      0, 0,     -1 },
	{ "Thunderbird",  NULL,       NULL,   1 << 1,       0,      0, 0,     -1 },
	{ "St",       NULL,       NULL,       1,       0,         1, 1,  -1 },
	{ NULL,  "Viber",       NULL,       1 << 3,       0,      0, 0,     -1 },
	{ "Slack",  NULL,       NULL,       1 << 3,       0,      0, 0,     -1 },
	{ "Mpv",  NULL,       NULL,       1 << 8,       0,        0, 0,   -1 },
	{ "Vlc",  NULL,       NULL,       1 << 8,       0,        0, 0,   -1 },
	{ "Subl3",  NULL,       NULL,       1 << 5,       0,      0, 0,     -1 },
	{ "Code",  NULL,       NULL,       1 << 5,       0,      0, 0,     -1 },
	{ "Gvim",  NULL,       NULL,       1 << 5,       0,       0, 0,    -1 },
	{ "Zathura",  NULL,       NULL,       1 << 6,       0,    0, 0,       -1 },
	{ "Sxiv",  NULL,       NULL,       1 << 6,       0,       0, 0,     -1 },
	{ "DesktopEditors",  NULL,       NULL,       1 << 6,       0, 0,0,           -1 },
	{ "Arandr",  NULL,       NULL,       1 << 7,       0, 0,0,           -1 },
	{ "Gufw.py",  NULL,       NULL,       1 << 7,       0, 0,0,           -1 },
	{ "org.remmina.Remmina",  NULL,       NULL,       1 << 8,       0,        0, 0,   -1 },
	{ "Filezilla",  NULL,       NULL,       1 << 8,       0,        0, 0,   -1 },

};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static int attachbelow = 1;    /* 1 means attach after the currently active window */

#include "gaplessgrid.c"
#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[3c]",      centeredmaster },
	{ "[3cf]",      centeredfloatingmaster },
    { "[G]",	  gaplessgrid },
 	{ "[Bs]",      spiral },
 	{ "[Bd]",     dwindle },
	{ "[D]",      deck },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *roficmd[] = { "rofi", "-show", "combi", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };
static const char *volmcmd[]       = { "amixer", "-q", "sset", "Master", "toggle", NULL };
static const char *voldcmd[]       = { "amixer", "-q", "sset", "Master", "5%-", NULL };
static const char *volucmd[]       = { "amixer", "-q", "sset", "Master", "5%+", NULL };
static const char *mpdstopcmd[]    = { "mpc", "toggle", NULL };
static const char *mpdprevcmd[]    = { "mpc", "prev", NULL };
static const char *mpdnextcmd[]    = { "mpc", "next", NULL };
//static const char *scrotcmd[]    = SHCMD("scrot && mv *_scrot.png ~/Pictures/");  //{"sleep 0.2;scrot", "&&", "mv", "*_scrot.png", "~/Pictures/",  NULL };
#include "focusurgent.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_a,      spawn,          {.v = roficmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
    { 0,                            XF86AudioLowerVolume, spawn, {.v = voldcmd } },
	{ 0,                            XF86AudioMute, spawn,        {.v = volmcmd } },
	{ 0,                            XF86AudioRaiseVolume, spawn, {.v = volucmd } },
    { 0,                            XF86AudioPrev, spawn, {.v = mpdprevcmd } },
	{ 0,                            XF86AudioPlay, spawn,        {.v = mpdstopcmd } },
	{ 0,                            XF86AudioNext, spawn, {.v = mpdnextcmd } },
    { 0,							XK_Print,  spawn,		   SHCMD("scrot && mv *_scrot.png ~/Pictures/") },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_w,      tabmode,        {-1} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
    { MODKEY|ControlMask,           XK_j,      pushdown,       {0} },
	{ MODKEY|ControlMask,           XK_k,      pushup,         {0} },
	{ MODKEY,                       XK_Left,   viewtoleft,     {0} },
	{ MODKEY,                       XK_Right,  viewtoright,    {0} },
	{ MODKEY|ShiftMask,             XK_Left,   tagtoleft,      {0} },
	{ MODKEY|ShiftMask,             XK_Right,  tagtoright,     {0} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[4]} },
    { MODKEY,                       XK_g,      setlayout,      {.v = &layouts[5]} },
    { MODKEY,                       XK_s,      setlayout,      {.v = &layouts[6]} },
    { MODKEY,                       XK_q,      setlayout,      {.v = &layouts[7]} },
	{ MODKEY,                       XK_c,      setlayout,      {.v = &layouts[8]} },
    { MODKEY,                       XK_Escape,           toggleAttachBelow,           {0} },
    /*{ MODKEY|ControlMask,		    XK_comma,  cyclelayout,    {.i = -1 } },*/
	{ MODKEY,                       XK_space, cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_0,      comboview,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      combotag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_t,      schemeToggle,   {0} },
	{ MODKEY|ShiftMask,             XK_z,      schemeCycle,    {0} },
	{ MODKEY,                       XK_n,      togglealttag,   {0} },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY,                       XK_y,      focusurgent,    {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTabBar,            0,              Button1,        focuswin,       {0} },
};

