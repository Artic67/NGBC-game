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

UBYTE spriteSizeX = 8;
UBYTE spriteSizeY = 16;
uint16_t currentSpriteNum = 0;
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

void newCollisionArea(CollisionArea* cl, uint16_t x, uint16_t y, uint8_t width, uint8_t height) {
    cl->posX = x;
    cl->posY = y;
    cl->width = width;
    cl->height = height;
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

void updateBlockSprite(HouseBlock* block, uint8_t charNumInSpritemap, uint8_t paletteNumber) {
    for(uint8_t i = 0; i < tilesInSprite; i++) {
        set_sprite_tile(block -> spriteIds[i], charNumInSpritemap * tilesInSprite + 2 * i);
        set_sprite_prop(block -> spriteIds[i], paletteNumber);
    }
}

void copyBlock(HouseBlock* a, HouseBlock* b) {
    b -> posX = a -> posX;
    b -> posY = a -> posY;
    b -> width = a -> width;
    b -> heigth = a -> heigth;
    b -> fallSpeed = a -> fallSpeed;
    b -> area = a -> area;
    for (int8_t i = 0; i < 8; i++) {
        b -> spriteIds[i] = a -> spriteIds[i];
    }
}

void changeFallSpeed(HouseBlock* block, int16_t fallSpeed) {
    block->fallSpeed = fallSpeed;
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

void placeBlock(HouseBlock* block) {
    changeFallSpeed(block, 0);
}

void spawnBlock(HouseBlock* block, CollisionArea* cl, uint16_t spriteNum, uint16_t charNumInSpritemap, uint16_t paletteNumber) {
    uint8_t startX = 72;
    uint8_t startY = 50;
    uint8_t width = 32;
    uint8_t height = 32;
    uint8_t fallSpeed = 0;

    newCollisionArea(cl, startX, startX, width, height);
    newBlock(block, cl, startX, startY, width, height, spriteNum, charNumInSpritemap, paletteNumber, fallSpeed);
    moveBlock(block, block->posX, block->posY);
}

UBYTE fallBlock(HouseBlock* block, CollisionArea* lastArea) {
    if (blocksColiding(block, lastArea)) {
        placeBlock(block);
        return 1;
    }
    block->posY += block->fallSpeed;
    block->area->posY = block->posY;
    moveBlock(block, block->posX, block->posY);
    return 0;
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

    CollisionArea ground = {40, 135, 96, 16};

    HouseBlock currentBlock;
    CollisionArea area;
    spawnBlock(&currentBlock, &area, currentSpriteNum, 0, 0);

    HouseBlock lastBlock;

    //HouseBlock currentBlock;
    //CollisionArea area = {72, 50, 32, 32};
    //newBlock(&currentBlock, &area, 72, 50, 32, 32, 0, 0, 0, 0);
    //moveBlock(&currentBlock, currentBlock.posX, currentBlock.posY);

    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    while (1) {
        
        UBYTE blockGrounded = fallBlock(&currentBlock, &ground);
        if (blockGrounded) {
            copyBlock(&currentBlock, &lastBlock);
            currentSpriteNum++;
            spawnBlock(&currentBlock, &area, currentSpriteNum, 0, 0);
        }
        if (joypad() & J_A) {
            if (currentBlock.fallSpeed == 0) {
                changeFallSpeed(&currentBlock, 3);
            }
        }
        if (joypad() & J_LEFT) {
            currentBlock.posX -= 2;
            moveBlock(&currentBlock, currentBlock.posX, currentBlock.posY);
        }
        if (joypad() & J_RIGHT) {
            currentBlock.posX += 2;
            moveBlock(&currentBlock, currentBlock.posX, currentBlock.posY);
        }
        if (joypad() & J_UP) {
            moveScreenUp(&screen, 1);
            renderLine(&screen);
        }
        betterDelay(3);
    }
    
}