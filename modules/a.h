#ifndef RICE_A
#define RICE_A

#include "./sway_a.h"
#include "./foot.h"
#include "./yambar_a.h"
#include "./fuzzel.h"
#include "./mako.h"
#include "./zathura_a.h"
#include "./bashrc_a.h"

struct a_conf {
	color_rgba fg;
	color_rgba bg;
	color_rgba active_bg;
	color_rgba accent_bg;
	color_rgba inactive_fg;
	char* font;
	size_t font_size;
	size_t font_size_small;

	bool display;
	char* display_name;

	bool bat0;
	bool bat1;

	char* start_icon;
	char* sway_extra_config;
	
	bool lidswitch_hack;
};


static inline void a( struct a_conf* c ) {

	add_package( "polkit" );
	add_package( "pipewire" );
	add_package( "wireplumber" );
	add_package( "brightnessctl" );
	add_package( "playerctl" );
	add_package( "swaybg" );
	add_package( "xdg-desktop-portal-wlr" );
	add_package( "grim" );
	add_package( "slurp" );
	add_package( "wl-clipboard" );
	add_package( "xorg-xwayland" );



	char *startup_progs[] = { 
		"yambar",
		"mako",
		"swaybg -i ~/.config/wallpaper.jpg",
		"playerctl daemon",
		"/usr/lib/xdg-desktop-portal -r",
		"/usr/lib/xdg-desktop-portal-wlr"
	};

	struct sway_config sway_config = {
		.exec_list = startup_progs,
		.num_execs = sizeof(startup_progs)/sizeof(char**),

		.monitor_options = 0,
		.num_monitor_options = 0,

		.term = "foot",
		
		.screenshot_command = "grim -t png -g \"$(slurp -d)\" - | wl-copy",
		.launcher_command = "fuzzel --no-exit-on-keyboard-focus-loss",

		.volume_up_command = "wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+",
		.volume_down_command = "wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-",
		.volume_mute_command = "wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle",

		.next_song_command = "playerctl next",
		.previous_song_command = "playerctl previous",
		.pause_play_song_command = "playerctl play-pause",
		.stop_song_command = "playerctl stop",

		.brightness_up_command = "brightnessctl s +10%",
		.brightness_down_command = "brightnessctl s 10%-",
		.statusbar_lidswitch_hack = c->lidswitch_hack

	};

	const char* workspace_list[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9"};

	struct yambar_config yambar_conf = {
		.fg = c->fg,
		.bg = c->bg,
		.active_bg = c->active_bg,
		.accent_bg = c->accent_bg,
		.inactive_fg = c->inactive_fg,
		.font = c->font,
		.font_size = c->font_size,
		.height = 32,

		.start_button = true,
		.start_text = "❖",
		.start_cmd = "swaymsg exec \"fuzzel --no-exit-on-keyboard-focus-loss\"",

		.i3_workspaces = true,
		.num_workspaces = 10,
		.workspace_list = workspace_list,
		.workspace_left_click_command = "swaymsg workspace number {name}",
		.workspace_active_left_click_command = "swaymsg workspace number {name}",
		.workspace_right_click_command = "swaymsg move container to workspace number {name}",
		.bat0 = 0,
		.bat1 = 0,
		.display = 0,
		.display_name = c->display_name,
		.brightness_up_command = "brightnessctl s +10%",
		.brightness_down_command = "brightnessctl s 10%-",
		.brightness_reset_command = "brightnessctl s 50%",

		.pipewire_wireplumber_audio = 1

	};

	if( c->start_icon )
		yambar_conf.start_text = c->start_icon;



	struct fuzzel_config fuzzel_conf = {
		.background = c->bg,
		.text = c->inactive_fg,
		.match = c->active_bg | 0x000000ff,
		.selection = c->accent_bg,
		.selection_text = c->fg,
		.selection_match = c->active_bg | 0x000000ff,
		.border = c->accent_bg,
	};

	struct mako_config mako_conf = {
		.font = c->font,
		.font_size = 16,
		.color_background = c->bg,
		.color_text = c->fg,
		.width = 450,
		.height = 100,
		.border_size = 4,
		.color_border = c->accent_bg,
		.border_radius = 12,
		.max_icon_size = 50,
		.icon_location = MAKO_ICON_LEFT,
		.timeout = 5000,
		.ignore_timeout = true,
		.anchor = MAKO_ANCHOR_BOTTOM_RIGHT
	};


	struct foot_config foot_conf = {
		.font = c->font,
		.font_size = c->font_size,
		.bg = c->bg,
		.fg = c->fg
	};

	struct bashrc_config bashrc_conf = {
		.extra_content = 0
	};

		sway( &sway_config );
		foot( &foot_conf );
		yambar( &yambar_conf );
		mako( &mako_conf );
		fuzzel( &fuzzel_conf );
		bashrc( &bashrc_conf );
		

}

#endif
