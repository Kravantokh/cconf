#ifndef MAKO_CONF_MODULE
#define MAKO_CONF_MODULE

#include "core.h"

enum mako_icon_location {
	MAKO_ICON_TOP = 0,
	MAKO_ICON_LEFT = 1,
	MAKO_ICON_BOTTOM = 2,
	MAKO_ICON_RIGHT = 3
};

enum mako_notification_anchor {
	MAKO_ANCHOR_TOP_CENTER,
	MAKO_ANCHOR_TOP_LEFT,
	MAKO_ANCHOR_CENTER_LEFT,
	MAKO_ANCHOR_BOTTOM_LEFT,
	MAKO_ANCHOR_BOTTOM_CENTER,
	MAKO_ANCHOR_BOTTOM_RIGHT,
	MAKO_ANCHOR_CENTER_RIGHT,
	MAKO_ANCHOR_TOP_RIGHT,
	MAKO_ANCHOR_CENTER
};

struct mako_config {
	char* font;
	size_t font_size;
	uint32_t color_background;
	uint32_t color_text;
	size_t width;
	size_t height;
	size_t border_size;
	uint32_t color_border;
	size_t border_radius;
	size_t max_icon_size;
	bool icon_show;
	enum mako_icon_location icon_location;
	size_t timeout;
	bool ignore_timeout; 
	enum mako_notification_anchor anchor;
};

static char* icon_locations[] = {
	[MAKO_ICON_TOP] = "top",
	[MAKO_ICON_LEFT] = "left",
	[MAKO_ICON_BOTTOM] = "bottom",
	[MAKO_ICON_RIGHT] = "right"
};

static char* anchor[] = {
	[MAKO_ANCHOR_TOP_CENTER] = "top-center",
	[MAKO_ANCHOR_TOP_LEFT] = "top-left",
	[MAKO_ANCHOR_CENTER_LEFT] = "center-left",
	[MAKO_ANCHOR_BOTTOM_LEFT] = "bottom-left",
	[MAKO_ANCHOR_BOTTOM_CENTER] = "bottom-center",
	[MAKO_ANCHOR_BOTTOM_RIGHT] = "bottom-right",
	[MAKO_ANCHOR_CENTER_RIGHT] = "center-right",
	[MAKO_ANCHOR_TOP_RIGHT] = "top-right",
	[MAKO_ANCHOR_CENTER] = "center",
};

static inline void mako( struct mako_config *conf ) {
	add_package( "mako" );
	ensure_path_exists_in_home(".config/mako");
	FILE* out = open_output_in_home(".config/mako/config");
	if( !out ) {
		fprintf( stderr, "Failed to open file .config/mako/config! It will not be written to!\n" );
		return;
	}

	fprintf( out, "font=%s", conf->font );
	if( conf->font_size )
		fprintf( out, ":size=%zu", conf->font_size );
	putc( '\n', out);

	fprintf( out, "background-color=#%8.8x\n", conf->color_background );
	fprintf( out, "text-color=#%8.8x\n", conf->color_text );

	if( conf->width )
		fprintf( out, "width=%zu\n", conf->width );

	if( conf->height )
		fprintf( out, "height=%zu\n", conf->height );

	if( conf->border_size )
		fprintf( out, "border-size=%zu\n", conf->border_size);

	if( conf->border_radius )
		fprintf( out, "border-radius=%zu\n", conf->border_radius);

	fprintf( out, "border-color=#%8.8x\n", conf->color_border );

	if( conf->max_icon_size )
		fprintf( out, "max-icon-size=%zu\n", conf->max_icon_size);

	fprintf( out, "icon-location=%s\n", icon_locations[conf->icon_location] );

	if( conf->timeout )
		fprintf( out, "default-timeout=%zu\n", conf->timeout);

	fprintf( out, "ignore-timeout=%d\n", conf->ignore_timeout );

	fprintf( out, "anchor=%s\n", anchor[conf->anchor] );

	fclose( out );
}


#endif
