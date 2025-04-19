#ifndef PROG_A_MODULE
#define PROG_A_MODULE

#include "./core.h"

static inline void prog_a(void) {
	add_package( "clang" );
	add_package( "gcc" );
	add_package( "tcc" );
	add_package( "lua" );
	add_package( "luajit" );
	add_package( "valgrind" );
	add_package( "git" );
	add_package( "ripgrep" );
}

#endif
