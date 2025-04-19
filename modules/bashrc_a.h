#ifndef CONF_BASHRC
#define CONF_BASHRC

#include "./core.h"

struct bashrc_config {
	char* extra_content;
};

void bashrc( struct bashrc_config *c ) {
	add_package( "bash" );

	FILE *o = open_output_in_home(".bashrc");

	fprintf( o,
		"alias ls='ls --color=auto'\n"
		"alias l='ls -l'\n"
		"alias ll='ls -la'\n"
		"alias ip='ip --color=auto'\n"
		"\n"
		"PS1='[\\u@\\h:\\w]\\$ '\n"
	);

	if( c->extra_content)
		fprintf( o, "%s", c->extra_content );

	fclose(o);
}

#endif
