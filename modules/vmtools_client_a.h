#ifndef VMTOOLS_CLIENT_A_MODULE
#define VMTOOLS_CLIENT_A_MODULE

#include "./core.h"

static inline void vmtools_client_a(void) {
	add_package( "moonlight-qt" );
	add_package( "wlvncc-git" );
	add_package( "rdesktop" );
}

#endif
