#ifndef YAMBAR_CONF_MODULE
#define YAMBAR_CONF_MODULE

#include "./core.h"

struct yambar_config {
	color_rgba fg;
	color_rgba bg;
	color_rgba active_bg;
	color_rgba accent_bg;
	color_rgba inactive_fg;
	char* font;
	size_t font_size;
	size_t height;

	bool start_button;
	char* start_text;
	char* start_cmd;

	bool i3_workspaces;
	size_t num_workspaces;
	const char* const* workspace_list;
	char* workspace_left_click_command;
	char* workspace_active_left_click_command;
	char* workspace_right_click_command;

	bool bat0;
	bool bat1;
	bool display;
	char* display_name;
	char* brightness_up_command;
	char* brightness_down_command;
	char* brightness_reset_command;

	bool pipewire_wireplumber_audio;
};

static inline void yambar( struct yambar_config *conf ) {

	add_package( "yambar" );
	add_package( "libmpdclient" );

	ensure_path_exists_in_home(".config/yambar");
	FILE* out = open_output_in_home(".config/yambar/config.yml");

	if( !out ) {
		fprintf( stderr, "Failed to open file ~/.config/yambar/config.yml! It will not be written to!\n" );
		return;
	}

	fprintf( out, 
	"audio_muted: &audio_muted %8.8x\n"
	"bar:\n"
	"  location: top\n"
	"  layer: bottom\n"
	"  height: %zu \n"
	"  spacing: 0\n"
	"  margin: 4\n"
	"  foreground: %8.8x\n"
	"  background: %8.8x\n"
	"  border:\n"
	"     width: 0\n"
	"     margin: 0\n"
	"     left-margin: 0\n"
	"     right-margin: 0\n",
	conf->inactive_fg,
	conf->height,
	conf->fg,
	conf->bg
	);

	fprintf( out,
	"  left:\n"
	);

	if( conf->start_button ) {
		fprintf( out, 
	"    - label:\n"
	"        content:\n"
	"          string:\n"
	"            left-margin: 5\n"
	"            right-margin: 10\n"
	"            text: %s\n"
	"            on-click:\n"
	"              left: %s\n",
			conf->start_text,
			conf->start_cmd
		);
	}

	fprintf( out,
	"    - clock:\n"
	"        time-format: \"%%l:%%M %%p\"\n"
	"        content:\n"
	"          list:\n"
	"            items:\n"
	"              - string:\n"
	"                  text: \"{time}\"\n"
	"                  right-margin: 15\n"
	);

	if( conf->i3_workspaces ) {
		fprintf( out, 
		"    - i3:\n" );
		if( conf->num_workspaces > 0 ) {
			fprintf( out,
			"        persistent:\n"
			);
			for( int i = 0; i < conf->num_workspaces - 1; ++i ) {
				fprintf( out, 
				"          - \"%s\"\n", conf->workspace_list[i]
				);
			}
		}
		fprintf( out,
		"        content:\n"
		"          \"\":\n"
		"            map:\n"
		"              default:\n"
		"                string:\n"
		"                  on-click:\n"
		"                    left: %s\n"
		"                    right: %s\n"
		"                  text: \" {name} \"\n"
		"                  font: %s\n"
		"                  foreground: %8.8x\n"
		"                  deco:\n"
		"                    stack:\n"
		"                    - background:\n"
		"                        color: %8.8x\n",
			conf->workspace_left_click_command,
			conf->workspace_right_click_command,
			conf->font,
			conf->fg,
			conf->accent_bg
		);

		fprintf( out,
		"              conditions:\n"
		"                empty:\n"
		"                  string:\n"
		"                    on-click:\n"
		"                      left: %s\n"
		"                      right: %s\n"
		"                    text: \" {name} \"\n"
		"                    font: %s\n"
		"                    foreground: %8.8x\n"
		"                    deco:\n"
		"                      stack:\n"
		"                      - background:\n"
		"                          color: %8.8x\n",
			conf->workspace_left_click_command,
			conf->workspace_right_click_command,
			conf->font,
			conf->fg,
			conf->bg
		);
		fprintf( out,
		"                state == focused:\n"
		"                  string:\n"
		"                    on-click:\n"
		"                      left: %s\n"
		"                    text: \" {name} \"\n"
		"                    font: %s:bold\n"
		"                    foreground: %8.8x\n"
		"                    deco:\n"
		"                      stack:\n"
		"                      - background:\n"
		"                          color: %8.8x\n",
			conf->workspace_active_left_click_command,
			conf->font,
			conf->fg,
			conf->active_bg
		);
		fprintf( out,
		"                state == urgent:\n"
		"                  string:\n"
		"                    text: \" {name} \"\n"
		"                    on-click:\n"
		"                      left: %s\n"
		"                      right: %s\n"
		"                    font: %s\n"
		"                    foreground: %8.8x\n"
		"                    deco:\n"
		"                      stack:\n"
		"                      - background:\n"
		"                          color: %8.8x\n",
			conf->workspace_left_click_command,
			conf->workspace_right_click_command,
			conf->font,
			conf->fg,
			conf->active_bg
		);
	}

	fprintf( out, "  right:\n" );

	if( conf->display ) {
		fprintf( out,
			"    - label:\n"
			"        content:\n"
			"          string:\n"
			"            right-margin: 5\n"
			"            text: \"💻\" \n"
			"    - backlight:\n"
			"        name: %s\n"
			"        content:\n"
			"          string:\n"
			"            right-margin: 10\n"
			"            text: \"{percent}%%\"\n"
			"            on-click:\n"
			"              wheel-up: %s\n"
			"              wheel-down: %s\n"
			"              middle: %s\n",
				conf->display_name,
				conf->brightness_up_command,
				conf->brightness_down_command,
				conf->brightness_reset_command
			);
	}

	if( conf->bat0 ) {
			fprintf( out, 
			"    - battery:\n"
			"        name: BAT0\n"
			"        poll-interval: 30000\n"
			"        content:\n"
			"          map:\n"
			"            conditions:\n"
			"              state == \"discharging\":\n"
			"                string:\n"
			"                  text: \"󰁾\"\n"
			"                  right-margin: 5\n"
			"              state == \"charging\":\n"
			"                string:\n"
			"                  text: \"󰂄\"\n"
			"                  right-margin: 5\n"
			"              state == \"full\":\n"
			"                string:\n"
			"                  text: \"󰁹\"\n"
			"                  right-margin: 5\n"
			"              state == \"not charging\":\n"
			"                string:\n"
			"                  text: \"󱈑\"\n"
			"                  right-margin: 5\n"
			"              state == \"unknown\":\n"
			"                string:\n"
			"                  text: \"󰂃\"\n"
			"                  right-margin: 5\n"
			"    - battery:\n"
			"        name: BAT0\n"
			"        poll-interval: 30000\n"
			"        content:\n"
			"          string:\n"
			"            text: \"{capacity}%%\"\n"
			"            right-margin: 10\n"
			);
		}

		if( conf->bat1 ) {
			fprintf( out, 
			"    - battery:\n"
			"        name: BAT1\n"
			"        poll-interval: 30000\n"
			"        content:\n"
			"          map:\n"
			"            conditions:\n"
			"              state == \"discharging\":\n"
			"                string:\n"
			"                  text: \"󰁾\"\n"
			"                  right-margin: 5\n"
			"              state == \"charging\":\n"
			"                string:\n"
			"                  text: \"󰂄\"\n"
			"                  right-margin: 5\n"
			"              state == \"full\":\n"
			"                string:\n"
			"                  text: \"󰁹\"\n"
			"                  right-margin: 5\n"
			"              state == \"not charging\":\n"
			"                string:\n"
			"                  text: \"󱈑\"\n"
			"                  right-margin: 5\n"
			"              state == \"unknown\":\n"
			"                string:\n"
			"                  text: \"󰂃\"\n"
			"                  right-margin: 5\n"
			"    - battery:\n"
			"        name: BAT1\n"
			"        poll-interval: 30000\n"
			"        content:\n"
			"          string:\n"
			"            text: \"{capacity}%%\"\n"
			"            right-margin: 10\n"
			);
		}

		if( conf->pipewire_wireplumber_audio ) {
			fprintf( out,
			"    - pipewire:\n"
			"        content:\n"
			"          map:\n"
			"            conditions:\n"
			"              type == \"sink\":\n"
			"                map:\n"
			"                  conditions:\n"
			"                    ~muted:\n"
			"                      ramp:\n"
			"                        tag: linear_volume\n"
			"                        items:\n"
			"                          - string:\n"
			"                              right-margin: 5\n"
			"                              text: \"🔈{linear_volume}%%\"\n"
			"                              on-click:\n"
			"                                wheel-up: wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%%+\n"
			"                                wheel-down: wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%%-\n"
			"                                middle: wpctl set-volume @DEFAULT_AUDIO_SINK@ 100%%\n"
			"                                left: wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle\n"
			"                          - string:\n"
			"                              right-margin: 5\n"
			"                              text: \"🔉{linear_volume}%%\"\n"
			"                              on-click:\n"
			"                                wheel-up: wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%%+\n"
			"                                wheel-down: wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%%-\n"
			"                                middle: wpctl set-volume @DEFAULT_AUDIO_SINK@ 100%%\n"
			"                                left: wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle\n"
			"                          - string:\n"
			"                              right-margin: 5\n"
			"                              text: \"🔊{linear_volume}%%\"\n"
			"                              on-click:\n"
			"                                wheel-up: wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%%+\n"
			"                                wheel-down: wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%%-\n"
			"                                middle: wpctl set-volume @DEFAULT_AUDIO_SINK@ 100%%\n"
			"                                left: wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle\n"
			"                    muted:\n"
			"                      ramp:\n"
			"                        tag: linear_volume\n"
			"                        items:\n"
			"                          - string:\n"
			"                              right-margin: 5\n"
			"                              text: \"🔈{linear_volume}%%\"\n"
			"                              foreground: *audio_muted\n"
			"                              on-click:\n"
			"                                wheel-up: wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%%+\n"
			"                                wheel-down: wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%%-\n"
			"                                middle: wpctl set-volume @DEFAULT_AUDIO_SINK@ 100%%\n"
			"                                left: wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle\n"
			"                          - string:\n"
			"                              right-margin: 5\n"
			"                              text: \"🔉{linear_volume}%%\"\n"
			"                              foreground: *audio_muted\n"
			"                              on-click:\n"
			"                                wheel-up: wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%%+\n"
			"                                wheel-down: wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%%-\n"
			"                                middle: wpctl set-volume @DEFAULT_AUDIO_SINK@ 100%%\n"
			"                                left: wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle\n"
			"                          - string:\n"
			"                              right-margin: 5\n"
			"                              text: \"🔊{linear_volume}%%\"\n"
			"                              foreground: *audio_muted\n"
			"                              on-click:\n"
			"                                wheel-up: wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%%+\n"
			"                                wheel-down: wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%%-\n"
			"                                middle: wpctl set-volume @DEFAULT_AUDIO_SINK@ 100%%\n"
			"                                left: wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle\n"
			"              type == \"source\":\n"
			"                map:\n"
			"                  conditions:\n"
			"                    ~muted:\n"
			"                      list:\n"
			"                        items:\n"
			"                          - string:\n"
			"                              right-margin: 5\n"
			"                              text: \"🎙{linear_volume}%%\"\n"
			"                              on-click:\n"
			"                                wheel-up: wpctl set-volume @DEFAULT_AUDIO_SOURCE@ 5%%+\n"
			"                                wheel-down: wpctl set-volume @DEFAULT_AUDIO_SOURCE@ 5%%-\n"
			"                                left: wpctl set-mute @DEFAULT_AUDIO_SOURCE@ toggle\n"
			"                                middle: wpctl set-volume @DEFAULT_AUDIO_SOURCE@ 100%%\n"
			"                    muted:\n"
			"                      list:\n"
			"                        items:\n"
			"                          - string:\n"
			"                              right-margin: 5\n"
			"                              text: \"🎙{linear_volume}%%\"\n"
			"                              foreground: *audio_muted\n"
			"                              on-click:\n"
			"                                wheel-up: wpctl set-volume @DEFAULT_AUDIO_SOURCE@ 5%%+\n"
			"                                wheel-down: wpctl set-volume @DEFAULT_AUDIO_SOURCE@ 5%%-\n"
			"                                left: wpctl set-mute @DEFAULT_AUDIO_SOURCE@ toggle\n"
			);
		}

	fclose( out );
}

#endif
