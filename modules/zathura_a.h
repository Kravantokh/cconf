#ifndef CONFIG_ZATHURA
#define CONFIG_ZATHURA

#include "./core.h"

struct zathura_config {
	color_rgba bg_color;
	color_rgba fg_color;
};

void zathura( struct zathura_config *c ) {

	add_package( "zathura" );
	add_package( "zathura-pdf-mupdf " );
	add_package( "zathura-djvu" );
	add_package( "zathura-ps" );

	ensure_path_exists_in_home(".config/zathura");
	FILE* out = open_output_in_home(".config/zathura/zathurarc");
	if( !out ) {
		fprintf( stderr, "Failed to open file .config/zathura/zathurarc! It will not be written to!\n" );
		return;
	}

	fprintf( out,
		"set recolor \"true\"\n"
		"set default-bg rgba(%u,%u,%u,%f)\n"
		"set recolor-lightcolor rgba(%u,%u,%u,%f)\n"
		"set adjust-open \"width\"\n",
		c->bg_color & 0xff >> 24, c->bg_color & 0x00ff >> 16, c->bg_color & 0x0000ff >> 8, (float)(c->bg_color & 0x000000ff)/255.0f,
		c->fg_color & 0xff >> 24, c->fg_color & 0x00ff >> 16, c->fg_color & 0x0000ff >> 8, (float)(c->fg_color & 0x000000ff)/255.0f
	);

	fclose( out );
}

#endif
