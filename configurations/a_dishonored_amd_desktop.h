#include "./themes/a_dishonored/theme.h"
#include "./modules/base.h"
#include "./modules/communication_a.h"
#include "./modules/firefox_a.h"
#include "./modules/media_a.h"
#include "./modules/neovim_a.h"
#include "./modules/office_a.h"
#include "./modules/prog_a.h"
#include "./modules/ssh_a.h"
#include "./modules/sys_util_a.h"
#include "./modules/vmtools_client_a.h"
#include "./modules/vmtools_host_a.h"
#include "./modules/web_util.h"
#include "./modules/wine_a.h"

CONFIGURE(

	struct a_conf a_conf = {
		.display = 0,
		.display_name = 0,
		.bat0 = false,
		.bat1 = false,
		.start_icon = 0,
		.sway_extra_config = 0,
		.lidswitch_hack = false,
	};

	struct base_config base_conf = {
		.kernel = KERNEL_LINUX_ZEN,
		.ucode = UCODE_AMD,
		.aur_manager = 0, // Use the default one (yay)
		.bootloader = BOOTLOADER_GRUB
	};

	struct firefox_a_conf firefox_conf = {
		.ublock = true,
		.decentraleyes = true,
		.noscript = true,
	};

	base( &base_conf );
	communication_a();
	firefox_a( &firefox_conf );
	media_a();
	neovim_a();
	office_a();
	prog_a();
	ssh_a();
	sys_util_a();
	vmtools_client_a();
	vmtools_host_a();
	web_util_a();
	wine_a();

	struct zathura_config zathura_conf = {
		.bg_color = a_conf.bg,
		.fg_color = a_conf.fg,
	};

	zathura( &zathura_conf );
	
	apply_theme( &a_conf );
	a(&a_conf);

	add_package( "blender" );
	add_package( "steam" );
	add_package( "podman" );
	add_package( "logseq-desktop-bin" );
	add_package( "prusa-slicer" );
)
