#ifndef BASE_MODULE
#define BASE_MODULE

#include "./core.h"

enum kernel_type {
	KERNEL_LINUX,
	KERNEL_LINUX_ZEN
};

enum ucode_type {
	UCODE_INTEL,
	UCODE_AMD
};

enum bootloader {
	BOOTLOADER_GRUB
};

struct base_config {
	enum kernel_type kernel;
	enum ucode_type ucode;
	char* aur_manager;
	enum bootloader bootloader;
};


static inline void base(struct base_config *c) {
	add_package( "base" );
	add_package( "base-devel" );
	add_package( "linux-firmware" );
	add_package( "pacman" );
	add_package( "mkinitcpio" );
	add_package( "efibootmgr" );
	if( !c->aur_manager )
		add_package( "yay" );

	switch( c->kernel ) {
		case KERNEL_LINUX:
			add_package("linux");
		break;
		case KERNEL_LINUX_ZEN:
			add_package("linux-zen");
		break;
	}
	switch( c->ucode ) {
	case UCODE_INTEL:
		add_package( "intel-ucode" );
	break;
	case UCODE_AMD:
		add_package( "amd-ucode" );
	break;
        }

	switch( c->bootloader ) {
		case BOOTLOADER_GRUB:
			add_package( "grub" );
		break;
	};
}

#endif
