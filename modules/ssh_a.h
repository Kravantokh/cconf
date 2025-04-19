#ifndef SSH_A_MODULE
#define SSH_A_MODULE

#include "./core.h"

static inline void ssh_a(void) {
	add_package( "waypipe" );
	add_package( "openssh" );
}

#endif
