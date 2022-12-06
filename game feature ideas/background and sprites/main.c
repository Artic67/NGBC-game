#include <stdio.h>
#include <gb/gb.h>
#include "bg.c"
#include "tilemap.c"
#include "FaceSprites.c"

void main() {

    uint8_t CharacterNum = 0;

    set_sprite_data(0, 2, Face);

    set_bkg_data(0, 8, Tilemap);
    set_bkg_tiles(0, 0, 40, 18, bg);

    set_sprite_tile(CharacterNum, 0);
    move_sprite(CharacterNum, 88,78);

    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    while (1) {
        scroll_bkg(1, 0);
        delay(100);
    }

}