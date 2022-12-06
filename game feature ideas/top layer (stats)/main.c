#include <stdio.h>
#include <gb/gb.h>
#include "bg.c"
#include "tilemap.c"
#include <gbdk/font.h>
#include "windowmap.c"

void main() {
    font_t minFont;

    font_init();
    minFont = font_load(font_min);
    font_set(minFont);

    set_bkg_data(37, 8, Tilemap);
    set_bkg_tiles(0, 0, 32, 18, bg);

    set_win_tiles(0, 0, 5, 1, windowMap);
    move_win(7, 120);

    SHOW_BKG;
    SHOW_WIN;
    DISPLAY_ON;

    while (1) {
        scroll_bkg(1, 0);
        delay(100);
    }

}