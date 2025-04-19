#include "../../modules/a.h"
#include "../../modules/core.h"

static inline void apply_theme( struct a_conf* c ) {

	c->bg = 0x000000bb,
	c->fg = 0xffffffff,
	c->active_bg = 0x7a9b9acc,
	c->accent_bg = 0x5e5e4a88,
	c->inactive_fg = 0x666666dd,
	c->font = "JetBrains Mono",
	c->font_size = 16,
	c->font_size_small = 12,

	add_package( "ttf-jetbrains-mono" );
	system( "cp ./themes/a_dishonored/wallpaper.jpg ~/.config/wallpaper.jpg");
}
