/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 7;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "FiraCode Nerd Font Mono:size=14" };
static const char dmenufont[]       = "FiraCode Nerd Font Mono:size=14";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#31353D";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
    	[SchemeNorm] = { col_gray3, col_gray1, col_gray1 },
    	[SchemeSel]  = { col_gray4, col_cyan,  col_gray3 },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const unsigned int ulinepad	= 5;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */

/*    class      				instance, title, tags, mask, isfloating, monitor */

// tag 0 ~ current workspace.

    { "Galculator", 	    			NULL, NULL, 0, 1,  -1 },
    { "Gnome-screenshot",   			NULL, NULL, 0, 1,  -1 },
    { "Peek",               			NULL, NULL, 0, 1,  -1 },
    { "Nl.hjdskes.gcolor3", 			NULL, NULL, 0, 1,  -1 },

// tag 1 ~ web browsing.

    { "firefox",            			NULL,  NULL,  1, 0, -1 },      
    { "firefox-developer-edition",      	NULL,  NULL,  1, 0, -1 },
    { "Tor Browser",            		NULL,  NULL,  1, 0, -1 },      
    { "Chromium",            			NULL,  NULL,  1, 0, -1 },      

// tag 2 ~ terminals.

    { "ghostty",        			NULL, NULL, 1 << 1, 0, -1 },
    { "Xfce4-terminal", 			NULL, NULL, 1 << 1, 0, -1 },

// tag 3 ~ text editors.

    { "dev.zed.Zed", 				NULL, NULL, 1 << 2, 0, -1 },
    { "Mousepad",    				NULL, NULL, 1 << 2, 0, -1 },

// tag 4 ~ file viewers.

    { "Evince",  				NULL, NULL, 1 << 3, 0, -1 },
    { "Ristretto",             			NULL, NULL, 1 << 3, 0, -1 },
    { "io.github.celluloid_player.Celluloid",   NULL, NULL, 1 << 3, 0, -1 },
    { "amberol",             			NULL, NULL, 1 << 3, 0, -1 },

// tag 5 ~ utils.

    { "pavucontrol", 	 			NULL, NULL, 1 << 4, 0, -1 },
    { "Blueman-manager", 			NULL, NULL, 1 << 4, 0, -1 },
    { "Catfish", 				NULL, NULL, 1 << 4, 0, -1 },
    { "Gnome-disks", 				NULL, NULL, 1 << 4, 0, -1 },
    { "Bitwarden", 				NULL, NULL, 1 << 4, 0, -1 },
    { "Uget-gtk", 				NULL, NULL, 1 << 4, 0, -1 },
    { "org.nicotine_plus.Nicotine", 		NULL, NULL, 1 << 4, 0, -1 },

// tag 6 ~ file manager.

    { "Thunar", 				NULL, NULL, 1 << 5, 0, -1 },

// tag 7 ~ creative suite.

    { "obsidian", 				"obsidian", "Dots", 1 << 6, 0, -1 },
    { "kolourpaint", 				NULL, NULL, 1 << 6, 0, -1 },
    { "kdenlive", 				NULL, NULL, 1 << 6, 0, -1 },

// tag 8 ~ obs.

    { "obs", 					"obs", "OBS", 1 << 7, 0, -1 },

};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "horizgrid.c"
#include "tcl.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "###",      horizgrid },
	{ "|||",      tcl },
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

static const char *appfinder[]  = {"xfce4-appfinder", NULL};
static const char *termcmd[]  = { "ghostty", NULL };
static const char *filemanager[]  = {"thunar", NULL};
static const char *editor[]  = {"zeditor", NULL};
static const char *printscr[] = {"gnome-screenshot", "-i", NULL};
static const char *colorpicker[]  = {"gcolor3", NULL};
static const char *volume[]   = {"pavucontrol", NULL};
static const char *bluetooth[]   = {"blueman-manager", NULL};
static const char *slock[]  = {"slock", NULL};

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = appfinder } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_k,      spawn,          {.v = filemanager } },
	{ MODKEY|ShiftMask,             XK_e,      spawn,          {.v = editor } },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = printscr } },
	{ MODKEY|ShiftMask,             XK_c,      spawn,          {.v = colorpicker } },
	{ MODKEY|ShiftMask,             XK_v,      spawn,          {.v = volume } },
	{ MODKEY|ShiftMask,             XK_b,      spawn,          {.v = bluetooth } },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },

	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_s,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },

	{ MODKEY|ShiftMask,             XK_l,      spawn,          {.v = slock } },
	{ MODKEY|ShiftMask,             XK_x,      quit,           {0} },

//	{ MODKEY,                       XK_b,      togglebar,      {0} },
//	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = +1 } },
//	{ MODKEY|ShiftMask,             XK_d,      incnmaster,     {.i = -1 } },
//	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
//	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
//	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
//	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
//	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
//	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
//	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
//	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
//	{ MODKEY|ShiftMask,             XK_h,      layoutscroll,   {.i = -1 } },
//	{ MODKEY|ShiftMask,             XK_l,      layoutscroll,   {.i = +1 } },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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
};

