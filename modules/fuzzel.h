#ifndef MODULE_FUZZEL
#define MODULE_FUZZEL

#include "./core.h"

struct fuzzel_config {
	color_rgba background;
	color_rgba text;
	color_rgba match;
	color_rgba selection;
	color_rgba selection_text;
	color_rgba selection_match;
	color_rgba border;
};

void fuzzel( struct fuzzel_config *c ) {
	add_package( "fuzzel" );
	ensure_path_exists_in_home( ".config/fuzzel" );
	FILE *o = open_output_in_home(".config/fuzzel/fuzzel.ini");

	fprintf( o, "[colors]\n" );
	fprintf( o, "background=%8.8x\n", c->background);
	fprintf( o, "text=%8.8x\n", c->text);
	fprintf( o, "match=%8.8x\n", c->match);
	fprintf( o, "selection=%8.8x\n", c->selection);
	fprintf( o, "selection-text=%8.8x\n", c->selection_text);
	fprintf( o, "selection-match=%8.8x\n", c->selection_match);
	fprintf( o, "border=%8.8x\n", c->border);

	fclose(o);
}



#endif
