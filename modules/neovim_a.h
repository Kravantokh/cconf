#ifndef NEOVIM_A_MODULE
#define NEOVIM_A_MODULE

#include "./core.h"

static inline void neovim_a(void) {
	add_package( "neovim" );
	printf( "Updating neovim config with git:\n" );
	fflush( stdout );
	system( "if cd ~/.config/nvim; then git pull; else git clone https://github.com/Kravantokh/nvim ~/.config/nvim; fi");

}

#endif
