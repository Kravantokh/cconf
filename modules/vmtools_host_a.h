#ifndef VMTOOLS_HOST_A_MODULE
#define VMTOOLS_HOST_A_MODULE

#include "./core.h"

static inline void vmtools_host_a(void) {
	add_package( "qemu-desktop" );
	add_package( "edk2-ovmf" );
}

#endif
