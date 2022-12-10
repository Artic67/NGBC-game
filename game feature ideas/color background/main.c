#include <gb/gb.h>
#include <gb/cgb.h>
#include "Map.h"
#include "MapSprites.h"

const UWORD bgpalette[] = {
    MapSpritesCGBPal0c0, MapSpritesCGBPal0c1, MapSpritesCGBPal0c2, MapSpritesCGBPal0c3,
    MapSpritesCGBPal1c0, MapSpritesCGBPal1c1, MapSpritesCGBPal1c2, MapSpritesCGBPal1c3,
    MapSpritesCGBPal2c0, MapSpritesCGBPal2c1, MapSpritesCGBPal2c2, MapSpritesCGBPal2c3,
    MapSpritesCGBPal3c0, MapSpritesCGBPal3c1, MapSpritesCGBPal3c2, MapSpritesCGBPal3c3,
};

void main() {

    set_bkg_palette(0, 4, bgpalette);

    set_bkg_data(0, 6, MapSprites);

    VBK_REG = VBK_BANK_1;
    set_bkg_tiles(0, 0, MapWidth, MapHeight, MapPLN1);

    VBK_REG = VBK_BANK_0;
    set_bkg_tiles(0, 0, MapWidth, MapHeight, MapPLN0);    

    SHOW_BKG;
    DISPLAY_ON;
    
}