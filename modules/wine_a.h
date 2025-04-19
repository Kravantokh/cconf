#ifndef WINE_A_MODULE
#define WINE_A_MODULE

#include "./core.h"

static inline void wine_a(void) {
	add_package( "wine" );
	add_package( "wine-mono" );
	add_package( "wine-gecko" );
	add_package( "winetricks" );
}

#endif
