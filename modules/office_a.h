#ifndef OFFICE_A_MODULE
#define OFFICE_A_MODULE

#include "./core.h"

static inline void office_a(void) {
	add_package( "libreoffice-fresh" );
	add_package( "obsidian" );
	add_package( "xournalpp" );
}

#endif
