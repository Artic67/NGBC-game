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

void newBlock(HouseBlock* block, CollisionArea* cl, uint16_t x, uint16_t y, uint8_t width, uint8_t height, uint8_t spriteNum, uint8_t charNumInSpritemap, uint8_t paletteNumber, uint8_t fallSpeed) {
    block -> posX = x;
    block -> posY = y;
    block -> width = width;
    block -> heigth = height;
    block -> fallSpeed = fallSpeed;
    block -> area = cl;

    for(uint8_t i = 0; i < tilesInSprite; i++) {
        set_sprite_tile(spriteNum * tilesInSprite + i, charNumInSpritemap * tilesInSprite + 2 * i);
        set_sprite_prop(spriteNum * tilesInSprite + i, paletteNumber);
        block -> spriteIds[i] = spriteNum * tilesInSprite + i;
    }
}

void newBlockL(HouseBlock* block, CollisionArea* cl, uint16_t x, uint16_t y, uint8_t spriteNum, uint8_t charNumInSpritemap, uint8_t paletteNumber) {
    uint8_t width = 32;
    uint8_t height = 32;
    uint8_t fallSpeed = 2;
    newBlock(block, cl, x, y, width, height, spriteNum, charNumInSpritemap, paletteNumber, fallSpeed);
}

void updateBlockSprite(HouseBlock* block, uint8_t charNumInSpritemap, uint8_t paletteNumber) {
    for(uint8_t i = 0; i < tilesInSprite; i++) {
        set_sprite_tile(block -> spriteIds[i], charNumInSpritemap * tilesInSprite + 2 * i);
        set_sprite_prop(block -> spriteIds[i], paletteNumber);
    }
}


UBYTE blocksColiding(HouseBlock* block, CollisionArea* lastArea) {
    CollisionArea* currArea = block -> area;

            // top left corner check
    return  (currArea->posX >= lastArea->posX && currArea->posX <= lastArea->posX + lastArea->width) &&
            (currArea->posY >= lastArea->posY && currArea->posY <= lastArea->posY + lastArea->height) ||

            // bot right corner check
            (lastArea->posX >= currArea->posX && lastArea->posX <= currArea->posX + currArea->width) &&
            (lastArea->posY >= currArea->posY && lastArea->posY <= currArea->posY + currArea->height) ||

            // top right left corner check
            (currArea->posX >= lastArea->posX && currArea->posX <= lastArea->posX + lastArea->width) &&
            (currArea->posY + currArea->height >= lastArea->posY && currArea->posY + currArea->height <= lastArea->posY + lastArea->height) ||
            
            // bot left corner check
            (lastArea->posX + lastArea->width >= currArea->posX && lastArea->posX + lastArea->width <= currArea->posX + currArea->width) &&
            (lastArea->posY >= currArea->posY && lastArea->posY <= currArea->posY + currArea->height);

}

void fallBlock(HouseBlock* block, CollisionArea* lastArea) {
    if (blocksColiding(block, lastArea)) {
        return;
    }
    block->posY += block->fallSpeed;
    block->area->posY = block->posY;
    moveBlock(block, block->posX, block->posY);
}

void main() {

    SPRITES_8x16;

    set_sprite_palette(0, 1, spritepalette);

    set_sprite_data(0, 16, BlockSpriteBlue);

    set_bkg_palette(0, 5, BGPalette);

    set_bkg_data(0, 31, BGTiles);
    


    VBK_REG = VBK_BANK_1;
    set_bkg_tiles(0, 0, screen.width, screen.height, BGPLN1Start);

    VBK_REG = VBK_BANK_0;
    set_bkg_tiles(0, 0, screen.width, screen.height, BGPLN0Start);

    CollisionArea area = {72, 50, 32, 32};
    HouseBlock genBlock;
    newBlockL(&genBlock, &area, 72, 50, 0, 0, 0);
    moveBlock(&genBlock, genBlock.posX, genBlock.posY);

    CollisionArea area2 = {40, 135, 96, 16};

    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    while (1) {
        
        fallBlock(&genBlock, &area2);

        if (joypad() & J_LEFT) {
            genBlock.posX -= 2;
            moveBlock(&genBlock, genBlock.posX, genBlock.posY);
        }
        if (joypad() & J_RIGHT) {
            genBlock.posX += 2;
            moveBlock(&genBlock, genBlock.posX, genBlock.posY);
        }
        if (joypad() & J_UP) {
            moveScreenUp(&screen, 1);
            renderLine(&screen);
        }
        betterDelay(3);
    }
    
}