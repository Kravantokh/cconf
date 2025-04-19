#ifndef SYS_UTIL_A_MODULE
#define SYS_UTIL_A_MODULE

#include "./core.h"

static inline void sys_util_a(void) {
	add_package( "ncdu" );
	add_package( "btop" );
	add_package( "nmap" );
	add_package( "bridge-utils" );
	add_package( "tree" );
}

#endif
