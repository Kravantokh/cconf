#ifndef NETWORKING_EXTRA_A_MODULE
#define NETWORKING_EXTRA_A_MODULE

#include "./core.h"

static inline void networking_extra_a(void) {
	add_package( "zerotier-one" );
	add_package( "syncthing" );
}

#endif
