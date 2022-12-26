#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdio.h>
#include "./src/HouseBlock.c"
#include "./src/Screen.c"
#include "./src/BlockSpriteBlue.h"
#include "./src/BlockSpriteBluePalette.c"
#include "./src/BG.h"
#include "./src/BGTiles.h"
#include "./src/BGTilesPalette.c"

HouseBlock block;
UBYTE spriteSizeX = 8;
UBYTE spriteSizeY = 16;
Screen screen = {20, 18, 0, 0, 32, 0};
unsigned char buffArr0[20];
unsigned char buffArr1[20];


void betterDelay(uint8_t numloops) {
    uint8_t i;
    for(i = 0; i < numloops; i++) {
        wait_vbl_done();
    }

}

void moveScreenUp(Screen* scr, int16_t y) {
    if (scr->posY - y < 0 || scr->posY - y > 256) {
        scr -> posY = 256 + scr->posY - y;
    } else {
        scr -> posY -= y;
    }
    move_bkg(scr->posX, scr->posY);
}

void getSlicedArray(unsigned char A[], unsigned char B[], uint16_t from, uint16_t num) {
    uint16_t i;
    for(i = from; i < from + num; i++) {
        B[i-from]=A[i];
        //printf("%u", B[i-from]);
        //betterDelay(10);
    }
}

void renderLine(Screen* scr) {
    int16_t tile = scr->posY / 8;

    //printf("%u ", tile);

    if (scr->lastRendered == tile) return;

    int16_t from = tile * scr->width;

    if (scr->lastTile == 1) {
        getSlicedArray(BGPLN0, buffArr0, 0, scr->width);
        getSlicedArray(BGPLN1, buffArr1, 0, scr->width);
    } else {
        getSlicedArray(BGPLN0, buffArr0, from, scr->width);
        getSlicedArray(BGPLN1, buffArr1, from, scr->width);
    }

    VBK_REG = VBK_BANK_1;
    set_bkg_tiles(0, tile, scr->width, 1, buffArr1);

    VBK_REG = VBK_BANK_0;
    set_bkg_tiles(0, tile, scr->width, 1, buffArr0);

    scr->lastRendered = tile;

    if (tile == 0 && scr->lastTile == 0) scr->lastTile = 1;
}

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

void main() {

    SPRITES_8x16;

    set_sprite_palette(0, 1, spritepalette);

    set_sprite_data(0, 16, BlockSpriteBlue);

    set_bkg_palette(0, 5, BGPalette);

    set_bkg_data(0, 31, BGTiles);
    


    VBK_REG = VBK_BANK_1;
    //unsigned char BGPLN1Slice[];
    //printf("%u %u", screenWidth * (BGHeight-screenHeight), screenWidth * screenHeight);
    //getSlicedArray(BGPLN1, BGPLN1Slice, screenWidth * (BGHeight-screenHeight), screenWidth * screenHeight);
    
    set_bkg_tiles(0, 0, screen.width, screen.height, BGPLN1Start);

    VBK_REG = VBK_BANK_0;
    //char BGPLN0Slice[];
    //getSlicedArray(BGPLN0, BGPLN0Slice, screenWidth * (BGHeight-screenHeight), 360);

    set_bkg_tiles(0, 0, screen.width, screen.height, BGPLN0Start);


    HouseBlock block1;
    newBlock(&block1, 50, 100, 32, 32, 0, 0);
    moveBlock(&block1, block1.xpos, block1.ypos);

    SHOW_BKG;
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
        if (joypad() & J_UP) {
            moveScreenUp(&screen, 1);
            renderLine(&screen);
        }
        betterDelay(3);
    }
    
}