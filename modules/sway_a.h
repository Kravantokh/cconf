#ifndef SWAY_CONF_MODULE
#define SWAY_CONF_MODULE

#include "./core.h"

enum sway_main_modifier {
	SWAY_MAIN_MOD_SUPER,
	SWAY_MAIN_MOD_ALT
};

struct sway_config {

	enum sway_main_modifier mod;

	char **exec_list;
	size_t num_execs;

	char **monitor_options;
	size_t num_monitor_options;

	char *term;

	char *screenshot_command;
	char *launcher_command;

	char *volume_up_command;
	char *volume_down_command;
	char *volume_mute_command;

	char *next_song_command;
	char *previous_song_command;
	char *pause_play_song_command;
	char *stop_song_command;

	char *brightness_down_command;
	char *brightness_up_command;

	bool statusbar_lidswitch_hack;

	char* extra_config;
};

static inline void sway( struct sway_config *c) {

	add_package( "sway" );

	ensure_path_exists_in_home( ".config/sway" );
	FILE *o = open_output_in_home( ".config/sway/config" );

	switch( c->mod ) {
		case SWAY_MAIN_MOD_ALT:
			fprintf( o, "set $mod Mod1\n" );
		default:
		case SWAY_MAIN_MOD_SUPER:
			fprintf( o, "set $mod Mod4\n" );
		break;
	}

	for( int i = 0; i < c->num_execs; ++i ) {
		fprintf( o, "exec %s\n", c->exec_list[i]);
	}


	fprintf( o, 
		"smart_gaps on\n"
		"gaps inner 6\n"
		"gaps outer -5\n"
		"default_border none\n"
		"default_floating_border none\n"
		"floating_modifier $mod\n"
	);

	fprintf( o, 
		"bindsym --no-repeat {\n"
		"	$mod+Ctrl+Shift+r reload\n"
		"	$mod+Ctrl+Shift+q exit\n"
		"	$mod+q kill\n"
		"	$mod+r exec %s\n"
		"	$mod+Return exec %s\n"
		"	$mod+p exec %s\n"
		"	XF86AudioPlay exec %s\n"
		"	XF86AudioPause exec %s\n"
		"	XF86AudioNext exec %s\n"
		"	XF86AudioPrev exec %s\n"
		"	XF86AudioStop exec %s\n"
		"	XF86AudioMute exec %s\n"
		"#	XF86Explorer exec\n"
		"#	XF86Search exec\n"
		"#	XF86Tools exec\n"
		"#	XF86Calculator exec\n"
		"}\n"
		"\n"
		"bindsym {\n"
		"	XF86AudioRaiseVolume exec %s\n"
		"	XF86AudioLowerVolume exec %s\n"
		"	XF86MonBrightnessUp  exec %s\n"
		"	XF86MonBrightnessDown exec %s\n"
		"}\n",

		c->launcher_command,
		c->term,
		c->screenshot_command,
		c->pause_play_song_command,
		c->pause_play_song_command,
		c->next_song_command,
		c->previous_song_command,
		c->stop_song_command,
		c->volume_mute_command,
		c->volume_up_command,
		c->volume_down_command,
		c->brightness_up_command,
		c->brightness_down_command
	);

	fprintf( o,
		"bindsym --no-repeat {\n"
		"	$mod+1 workspace number 1\n"
		"	$mod+2 workspace number 2\n"
		"	$mod+3 workspace number 3\n"
		"	$mod+4 workspace number 4\n"
		"	$mod+5 workspace number 5\n"
		"	$mod+6 workspace number 6\n"
		"	$mod+7 workspace number 7\n"
		"	$mod+8 workspace number 8\n"
		"	$mod+9 workspace number 9\n"
		"	$mod+0 workspace number 10\n"
		"\n"
		"	$mod+Shift+1 move container to workspace number 1\n"
		"	$mod+Shift+2 move container to workspace number 2\n"
		"	$mod+Shift+3 move container to workspace number 3\n"
		"	$mod+Shift+4 move container to workspace number 4\n"
		"	$mod+Shift+5 move container to workspace number 5\n"
		"	$mod+Shift+6 move container to workspace number 6\n"
		"	$mod+Shift+7 move container to workspace number 7\n"
		"	$mod+Shift+8 move container to workspace number 8\n"
		"	$mod+Shift+9 move container to workspace number 9\n"
		"	$mod+Shift+0 move container to workspace number 10\n"
		"}\n"
		"\n"
		"bindsym $mod+w mode \"Window Management\"\n"
		"bindsym $mod+a mode \"Language\"\n"
		"bindsym $mod+Shift+r mode \"Launch\"\n"
		"bindsym $mod+s mode \"Settings\n"
		"\n"
		"mode \"Window Management\" {\n"
		"	bindsym --no-repeat {\n"
		"		q kill; mode \"default\"\n"
		"		Shift+f fullscreen toggle; mode \"default\"\n"
		"		f floating toggle; mode \"default\"\n"
		"		Escape mode \"default\"\n"
		"		Return mode \"default\"\n"
		"	}\n"
		"}\n"
		"\n"
		"\n"
		"mode \"Settings\" {\n"
		"	bindsym --no-repeat {\n"
		"		l input type:pointer left_handed enabled; mode \"default\"\n"
		"		r input type:pointer left_handed disabled; mode \"default\"\n"
		"		Escape mode \"default\"\n"
		"		Return mode \"default\"\n"
		"	}\n"
		"}\n"
		"\n"
		"mode \"Handedness\" {\n"
		"	bindsym --no-repeat {\n"
		"		l input type:pointer left_handed enabled; mode \"default\"\n"
		"		r input type:pointer left_handed disabled; mode \"default\"\n"
		"		Escape mode \"Settings\"\n"
		"		Return mode \"Settings\"\n"
		"	}\n"
		"}\n"
		"\n"
		"mode \"Language\" {\n"
		"	bindsym --no-repeat {\n"
		"		m exec swaymsg input type:keyboard xkb_layout hu\\(qwerty\\); mode \"default\"\n"
		"		e exec swaymsg input type:keyboard xkb_layout us; mode \"default\"\n"
		"		d exec swaymsg input type:keyboard xkb_layout de; mode \"default\"\n"
		"		r exec swaymsg input type:keyboard xkb_layout ro\\(std\\); mode \"default\"\n"
		"		Escape mode \"default\"\n"
		"		Return mode \"default\"\n"
		"	}\n"
		"}\n"
		"\n"
		"# Run mode\n"
		"mode \"Launch\" {\n"
		"	bindsym --no-repeat {\n"
		"		f exec firefox; mode \"default\"\n"
		"		t exec $term; mode \"default\"\n"
		"		Escape mode \"default\"\n"
		"		Return mode \"default\"\n"
		"	}\n"
		"}\n"
	);

	if( c->statusbar_lidswitch_hack ) {
		fprintf( o, 
			"bindswitch --reload --locked lid:on output $laptop disable; exec killall yambar; exec sleep 1; exec yambar\n"
			"bindswitch --reload --locked lid:off output $laptop enable; exec killall yambar; exec sleep 1; exec yambar\n"
		);
	}

	if( c->extra_config ) {
		fprintf( o, "%s", c->extra_config );
	}

	fclose(o);
}

#endif
