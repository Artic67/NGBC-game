#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdio.h>
#include "./src/HouseBlock.c"
#include "./src/BlockSpriteBlue.h"
#include "./src/BlockSpriteBluePalette.c"

HouseBlock block;
UBYTE spriteSizeX = 8;
UBYTE spriteSizeY = 16;

void moveBlock(HouseBlock* block, uint8_t x, uint8_t y) {
    move_sprite(block -> spriteIds[0], x, y);
    move_sprite(block -> spriteIds[1], x + spriteSizeX, y);
    move_sprite(block -> spriteIds[2], x + 2 * spriteSizeX, y);
    move_sprite(block -> spriteIds[3], x + 3 * spriteSizeX, y);
    move_sprite(block -> spriteIds[4], x, y + spriteSizeY);
    move_sprite(block -> spriteIds[5], x + spriteSizeX, y + spriteSizeY);
    move_sprite(block -> spriteIds[6], x + 2 * spriteSizeX, y + spriteSizeY);
    move_sprite(block -> spriteIds[7], x + 3 * spriteSizeX, y + spriteSizeY);
}

void newBlock(HouseBlock* block, uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t charNumInSpritemap, uint8_t paletteNumber) {
    block -> xpos = x;
    block -> ypos = y;
    block -> width = width;
    block -> heigth = height;

    for(uint8_t i = 0; i < tilesInSprite; i++) {
        set_sprite_tile(charNumInSpritemap * tilesInSprite + i, charNumInSpritemap * tilesInSprite + 2 * i);
        set_sprite_prop(charNumInSpritemap * tilesInSprite + i, paletteNumber);
        block -> spriteIds[i] = charNumInSpritemap * tilesInSprite + i;
    }
}

void betterDelay(uint8_t numloops) {
    uint8_t i;
    for(i = 0; i < numloops; i++) {
        wait_vbl_done();
    }

}

void main() {

    SPRITES_8x16;

    set_sprite_palette(0, 1, spritepalette);

    set_sprite_data(0, 16, BlockSpriteBlue);

    

    HouseBlock block1;
    newBlock(&block1, 50, 100, 32, 32, 0, 0);
    

    moveBlock(&block1, block1.xpos, block1.ypos);

    SHOW_SPRITES;
    DISPLAY_ON;

    while (1) {
        if (joypad() & J_LEFT) {
            block1.xpos -= 2;
            moveBlock(&block1, block1.xpos, block1.ypos);
        }
        if (joypad() & J_RIGHT) {
            block1.xpos += 2;
            moveBlock(&block1, block1.xpos, block1.ypos);
        }
        betterDelay(3);
    }
    
}