#ifndef FIREFOX_A_MODULE
#define FIREFOX_A_MODULE

#include "./core.h"

struct firefox_a_conf {
	bool ublock;
	bool decentraleyes;
	bool noscript;
};

static inline void firefox_a( struct firefox_a_conf* c ) {
	add_package( "firefox" );
	if( c->ublock )
		add_package( "firefox-ublock-origin" );
	if( c->decentraleyes )
		add_package( "firefox-decentraleyes" );
	if( c->noscript )
		add_package( "firefox-noscript" );
}

#endif
