#ifndef FOOT_CONFIG
#define FOOT_CONFIG

#include "./core.h"

struct foot_config {
	char* font;
	size_t font_size;
	size_t resize_delay;
	color_rgba bg;
	color_rgba fg;
	struct ansi_term_colors *colors;
};


static inline void foot( struct foot_config *c ) {
	add_package( "foot" );

	ensure_path_exists_in_home( ".config/foot" );
	FILE *o = open_output_in_home(".config/foot/foot.ini");

	fprintf( o, 
		"font=%s:size=%zu\n"
		"font-bold=%s:size=%zu:style=Bold\n"
		"font-italic=%s:size=%zu:style=Italic\n"
		"dpi-aware=false\n"
		"\n"
		"resize-delay-ms=100\n"
		"\n"
		"[colors]\n"
		"alpha=%f\n"
		"foreground=%6.6x\n"
		"background=%6.6x\n",

		c->font, c->font_size,
		c->font, c->font_size,
		c->font, c->font_size,

		(float)(c->bg & 0xff)/255.0,
		c->fg >> 8,
		c->bg >> 8
	);

}

#endif
