/* See LICENSE file for copyright and license details. */
#include "key_codes.h"
/* appearance */
static const unsigned int borderpx	= 2;	/* border pixel of windows */
static const unsigned int gappx		= 18;	/* gap pixel between windows */
static const unsigned int snap		= 32;	/* snap pixel */
static const int showbar			= 1;	/* 0 means no bar */
static const int topbar				= 1;	/* 0 means bottom bar */

static const char *fonts[] ={	"Font Awesome 5 Brands:size=20",
								"Font Awesome 5 Free:size=20",
								"FontAwesome:size=20",
								"Liberation Mono:size=18"
							};
static const char dmenufont[]		= "monospace:size=18";

static const char col_gray1[]		= "#222222";
static const char col_gray2[]		= "#444444";
static const char col_gray3[]		= "#BBBBBB";
static const char col_gray4[]		= "#EEEEEE";
static const char col_cyan[]		= "#005577";
static const char col_purp[]		= "#B85DE9";
static const char *colors[][3]		= {
	/*					fg			bg		border   */
	[SchemeNorm] = {col_gray3, col_gray1,	col_gray2},
	[SchemeSel]  = {col_gray1, col_gray4,	col_gray3},
};

/* tagging */
static const char *tags[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class		instance	title		tags mask		isfloating		monitor */
	{"Gimp",		NULL,		NULL,		0,				1,				-1},
	{"firefox",		"Devtools",	NULL,		0,				1,				-1},
};

/* layout(s) */
static const float mfact		= 0.55;		/* factor of master area size [0.05..0.95] */
static const int nmaster		= 1;		/* number of clients in master area */
static const int resizehints	= 1;		/* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol		arrange function */
	{"[]=",			tile},		/* first entry is default */
	{"><>",			NULL},		/* no layout function means floating behavior */
	{"[M]",			monocle},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{MODKEY,						KEY,	view,		{.ui = 1 << TAG}},	\
	{MODKEY|ControlMask,			KEY,	toggleview,	{.ui = 1 << TAG}},	\
	{MODKEY|ShiftMask,				KEY,	tag,		{.ui = 1 << TAG}},	\
	{MODKEY|ControlMask|ShiftMask,	KEY,	toggletag,	{.ui = 1 << TAG}},	\
	{Mod1Mask|ShiftMask,			KEY,	tagview,	{.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) {.v = (const char*[]){"/bin/sh", "-c", cmd, NULL}}

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {"dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL};
static const char *termcmd[]  = {"alacritty", NULL};

static Key keys[] = {
	/* modifier						key							function			argument */
	{ MODKEY,						KC_p,						spawn,				{.v = dmenucmd}},		// p
	{ MODKEY|ShiftMask,				KC_return,					spawn,				{.v = termcmd}},		// Return
	{ MODKEY,						KC_b,						togglebar,			{0}},					// b
	{ MODKEY,						KC_j,						focusstack,			{.i = +1}},				// j
	{ MODKEY,						KC_k,						focusstack,			{.i = -1}},				// k
	{ MODKEY,						KC_i,						incnmaster,			{.i = +1}},				// i
	{ MODKEY,						KC_d,						incnmaster,			{.i = -1}},				// d
	{ MODKEY,						KC_h,						setmfact,			{.f = -0.05}},			// h
	{ MODKEY,						KC_l,						setmfact,			{.f = +0.05}},			// l
	{ MODKEY,						KC_return,					zoom,				{0}},					// Return
	{ MODKEY,						KC_Tab,						view,				{0}},					// Tab
	{ MODKEY|ShiftMask,				KC_c,						killclient,			{0}},					// c
	{ MODKEY,						KC_t,						setlayout,			{.v = &layouts[0]}},	// t
	{ MODKEY,						KC_f,						setlayout,			{.v = &layouts[1]}},	// f
	{ MODKEY,						KC_m,						setlayout,			{.v = &layouts[2]}},	// m
	{ MODKEY,						KC_space,					setlayout,			{0}},					// space
	{ MODKEY|ShiftMask,				KC_space,					togglefloating,		{0}},					// space
	{ MODKEY,						KC_0,						view,				{.ui = ~0}},			// 0
	{ MODKEY|ShiftMask,				KC_0,						tag,				{.ui = ~0}},			// 0
	{ MODKEY,						KC_comma,					focusmon,			{.i = -1}},				// comma
	{ MODKEY,						KC_period,					focusmon,			{.i = +1}},				// period
	{ MODKEY|ShiftMask,				KC_comma,					tagmon,				{.i = -1}},				// comma
	{ MODKEY|ShiftMask,				KC_period,					tagmon,				{.i = +1}},				// period
	{ MODKEY|ShiftMask,				KC_q,						quit,				{0}},					// q
	// My Custom Keybindings
	{MODKEY|ShiftMask,				KC_r,						quit,				{1}},
	{MODKEY,						KC_r,						refreshmon,			{0}},
	{MODKEY,						KC_w,						spawn,				SHCMD("~/Devel/suckless/dmenu/scripts/firefox-profile.sh")},
	{0,								KC_mon_brightness_up,		spawn,				SHCMD("xbacklight -inc 10")},
	{0,								KC_mon_brightness_down,		spawn,				SHCMD("xbacklight -dec 10")},
	{0,								KC_audio_raise_volume,		spawn,				SHCMD("pulseaudio-ctl up")},
	{0,								KC_audio_lower_volume,		spawn,				SHCMD("pulseaudio-ctl down")},
	{0,								KC_audio_mute,				spawn,				SHCMD("pulseaudio-ctl mute")},
	{0,								KC_audio_toggle,			spawn,				SHCMD("playerctl play-pause")},
	{0,								KC_audio_pause,				spawn,				SHCMD("playerctl pause")},
	{0,								KC_audio_play,				spawn,				SHCMD("playerctl play-pause")},
	{0,								KC_audio_next,				spawn,				SHCMD("playerctl next")},
	{0,								KC_audio_prev,				spawn,				SHCMD("playerctl previous")},
	// Tag Keys defined with macro
	TAGKEYS(						KC_1,						0)// 1
	TAGKEYS(						KC_2,						1)// 2
	TAGKEYS(						KC_3,						2)// 3
	TAGKEYS(						KC_4,						3)// 4
	TAGKEYS(						KC_5,						4)// 5
	TAGKEYS(						KC_6,						5)// 6
	TAGKEYS(						KC_7,						6)// 7
	TAGKEYS(						KC_8,						7)// 8
	TAGKEYS(						KC_9,						8)// 9
};
/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click				event mask 		button			function		argument */
	{ClkLtSymbol,			0,				Button1,		setlayout,		{0}},
	{ClkLtSymbol,			0,				Button3,		setlayout,		{.v = &layouts[2]}},
	{ClkWinTitle,			0,				Button2,		zoom,			{0}},
	{ClkStatusText,			0,				Button2,		spawn,			{.v = termcmd}},
	{ClkClientWin,			MODKEY,			Button1,		movemouse,		{0}},
	{ClkClientWin,			MODKEY,			Button2,		togglefloating,	{0}},
	{ClkClientWin,			MODKEY,			Button3,		resizemouse,	{0}},
	{ClkTagBar,				0,				Button1,		view,			{0}},
	{ClkTagBar,				0,				Button3,		toggleview,		{0}},
	{ClkTagBar,				MODKEY,			Button1,		tag,			{0}},
	{ClkTagBar,				MODKEY,			Button3,		toggletag,		{0}},

	// Logitec mouse buttons
	{ClkRootWin,			0,				Button9,		inctag,			{.i = +1}},
	{ClkClientWin,			0,				Button9,		inctag,			{.i = +1}},
	{ClkRootWin,			0,				Button8,		inctag,			{.i = -1}},
	{ClkClientWin,			0,				Button8,		inctag,			{.i = -1}},

	{ClkClientWin,			MODKEY,			Button9,		tagmon,			{.i = +1}},
	{ClkClientWin,			MODKEY,			Button8,		tagmon,			{.i = -1}},

	{ClkClientWin,			Mod1Mask,		Button9,		folwin,			{.i = +1}},
	{ClkClientWin,			Mod1Mask,		Button8,		folwin,			{.i = -1}},


	{ClkRootWin,			0,				Button7,		spawn,			SHCMD("pulseaudio-ctl up")},
	{ClkClientWin,			0,				Button7,		spawn,			SHCMD("pulseaudio-ctl up")},
	{ClkRootWin,			0,				Button6,		spawn,			SHCMD("pulseaudio-ctl down")},
	{ClkClientWin,			0,				Button6,		spawn,			SHCMD("pulseaudio-ctl down")},
};

