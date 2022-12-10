#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdio.h>
#include "Sprites.h"

const UWORD bgpalette[] = {
    RGB_DARKGRAY,
    RGB_DARKGRAY,
    RGB_DARKGRAY,
    RGB_DARKGRAY
};

const UWORD spritepalette[] = {
    SpritesCGBPal0c0,
    SpritesCGBPal0c1,
    SpritesCGBPal0c2,
    SpritesCGBPal0c3,

    SpritesCGBPal1c0,
    SpritesCGBPal1c1,
    SpritesCGBPal1c2,
    SpritesCGBPal1c3,

    SpritesCGBPal2c0,
    SpritesCGBPal2c1,
    SpritesCGBPal2c2,
    SpritesCGBPal2c3
};



void main() {

    SPRITES_8x16;

    set_bkg_palette(0, 1, bgpalette);

    set_sprite_palette(0, 3, spritepalette);

    set_sprite_data(0, 6, Sprites);

    set_sprite_tile(0, 0);
    set_sprite_prop(0, 0);
    move_sprite(0, 20, 80);

    set_sprite_tile(1, 2);
    set_sprite_prop(1, 1);
    move_sprite(1, 80, 80);

    set_sprite_tile(2, 4);
    set_sprite_prop(2, 2);
    move_sprite(2, 140, 80);


    SHOW_SPRITES;
    SHOW_BKG;
    DISPLAY_ON;
}