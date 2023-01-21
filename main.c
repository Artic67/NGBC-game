#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdio.h>
#include "./src/HouseBlock.c"
#include "./src/Screen.c"
#include "./src/Wire.c"
#include "./src/BlockSpriteBlue.h"
#include "./src/BlockSpriteBluePalette.c"
#include "./src/BG.h"
#include "./src/BGTiles.h"
#include "./src/BGTilesPalette.c"
#include "./src/Rope.h"
#include "./src/RopePalette.c"

const uint8_t MIN_BLOCK_X = 20;
const uint8_t MAX_BLOCK_X = 60 + 96 - 32;
const UBYTE moveBGFromBlock = 3;

const uint16_t speedToBlockCount[8] = {
    10,
    20,
    50,
    100,
    200,
    500,
    1000,
    2000
};

int16_t blockCount = 0;
UBYTE movingAllowed = 0;
UBYTE startMoving = 0;
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

int16_t calculateMoveSpeedX(uint16_t stbc[], uint16_t blocksCount) {
    for (uint8_t i = 0; i < 8; i++) {
        if (blocksCount < stbc[i]) {
            return i + 1;
        }
    }
    return 8;
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

void moveWire(Wire* wire, uint8_t x, uint8_t y) {
    move_sprite(wire -> spriteIds[0], x, y);
    move_sprite(wire -> spriteIds[1], x, y + spriteSizeY);
}

void newCollisionArea(CollisionArea* cl, uint16_t x, uint16_t y, uint8_t width, uint8_t height) {
    cl->posX = x;
    cl->posY = y;
    cl->width = width;
    cl->height = height;
}

void newBlock(HouseBlock* block, CollisionArea* cl, uint16_t x, uint16_t y, uint8_t width, uint8_t height, uint8_t spriteNum, uint8_t charNumInSpritemap, uint8_t paletteNumber, uint8_t fallSpeed, int8_t moveSpeedX) {
    block -> posX = x;
    block -> posY = y;
    block -> width = width;
    block -> height = height;
    block -> fallSpeed = fallSpeed;
    block -> moveSpeedX = moveSpeedX;
    block -> area = cl;

    for(uint8_t i = 0; i < tilesInBlockSprite; i++) {
        set_sprite_tile(spriteNum * tilesInBlockSprite + i, charNumInSpritemap * tilesInBlockSprite + 2 * i);
        set_sprite_prop(spriteNum * tilesInBlockSprite + i, paletteNumber);
        block -> spriteIds[i] = spriteNum * tilesInBlockSprite + i;
    }
}

void newWire(Wire* wire, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t spriteNumber, uint16_t charNumInSpritemap, uint16_t paletteNumber) {
    wire -> posX = x;
    wire -> posY = y;
    wire -> width = width;
    wire -> height = height;

    for(uint8_t i = 0; i < tilesInWireSprite; i++) {
        set_sprite_tile(spriteNumber + i, charNumInSpritemap + tilesInWireSprite * i);
        set_sprite_prop(spriteNumber + i, paletteNumber);
        wire -> spriteIds[i] = spriteNumber + i;
    }
}

void updateBlockSprite(HouseBlock* block, uint8_t charNumInSpritemap, uint8_t paletteNumber) {
    for(uint8_t i = 0; i < tilesInBlockSprite; i++) {
        set_sprite_tile(block -> spriteIds[i], charNumInSpritemap * tilesInBlockSprite + 2 * i);
        set_sprite_prop(block -> spriteIds[i], paletteNumber);
    }
}

void copyBlock(HouseBlock* a, HouseBlock* b) {
    b -> posX = a -> posX;
    b -> posY = a -> posY;
    b -> width = a -> width;
    b -> height = a -> height;
    b -> fallSpeed = a -> fallSpeed;
    b -> moveSpeedX = a -> moveSpeedX;
    b -> area = a -> area;
    for (int8_t i = 0; i < 8; i++) {
        b -> spriteIds[i] = a -> spriteIds[i];
    }
}

void makeCollisionAreaFromBlock(CollisionArea* cl, HouseBlock* block) {
    cl->posX = block->area->posX;
    cl->posY = block->area->posY;
    cl->height = block->area->height;
    cl->width = block->area->width;
    //printf("%u   %u   %u   %u ", cl->posX, cl->posY, cl->height, cl->width);
}

void changeFallSpeed(HouseBlock* block, int16_t fallSpeed) {
    block->fallSpeed = fallSpeed;
}

void changeMoveSpeedX(HouseBlock* block, int16_t moveSpeedX) {
    block->moveSpeedX = moveSpeedX;
}

UBYTE blocksColiding(HouseBlock* block, CollisionArea* B) {
    CollisionArea* A = block -> area;
    
            // bot right
    return  (A->posX + A->width >= B->posX && A->posX + A->width <= B->posX + B->width) && (A->posY + A->height >= B->posY && A->posY + A->height <= B->posY + B->height) ||
            // bot left
            (A->posX >= B->posX && A->posX <= B->posX + B->width) && (A->posY + A->height >= B->posY && A->posY + A->height <= B->posY + B->height) ||
            // top left
            (A->posX >= B->posX && A->posX <= B->posX + B->width) && (A->posY >= B->posY && A->posY <= B->posY + B->height) ||
            // top right
            (A->posX + A->width >= B->posX && A->posX + A->width <= B->posX + B->width) && (A->posY >= B->posY && A->posY <= B->posY + B->height);

            // top left corner check
    //return  (currArea->posX >= lastArea->posX && currArea->posX <= lastArea->posX + lastArea->width) &&
    //        (currArea->posY >= lastArea->posY && currArea->posY <= lastArea->posY + lastArea->height) ||

            // bot right corner check
    //        (lastArea->posX >= currArea->posX && lastArea->posX <= currArea->posX + currArea->width) &&
    //        (lastArea->posY >= currArea->posY && lastArea->posY <= currArea->posY + currArea->height) ||

            // top right left corner check
    //        (currArea->posX >= lastArea->posX && currArea->posX <= lastArea->posX + lastArea->width) &&
    //        (currArea->posY + currArea->height >= lastArea->posY && currArea->posY + currArea->height <= lastArea->posY + lastArea->height) ||
            
            // bot left corner check
    //        (lastArea->posX + lastArea->width >= currArea->posX && lastArea->posX + lastArea->width <= currArea->posX + currArea->width) &&
    //        (lastArea->posY >= currArea->posY && lastArea->posY <= currArea->posY + currArea->height);

}

void placeBlock(HouseBlock* block) {
    changeFallSpeed(block, 0);
    changeMoveSpeedX(block, 0);
}

UBYTE checkXBorders(HouseBlock* block) {
    //printf("%u < %u || %u > %u ", block->posX + block->moveSpeedX,MAX_BLOCK_X, block->posX + block->moveSpeedX, MIN_BLOCK_X);
    if (block->posX + block->moveSpeedX > MAX_BLOCK_X || block->posX + block->moveSpeedX < MIN_BLOCK_X) {
        return FALSE;
    }
    return TRUE;
}

void spawnBlock(HouseBlock* block, CollisionArea* cl, int8_t moveSpeedX, uint16_t spriteNum, uint16_t charNumInSpritemap, uint16_t paletteNumber) {
    uint8_t startX = 72;
    uint8_t startY = 48;
    uint8_t width = 32;
    uint8_t height = 32;
    uint8_t fallSpeed = 0;

    newCollisionArea(cl, startX, startY, width, height);
    newBlock(block, cl, startX, startY, width, height, spriteNum, charNumInSpritemap, paletteNumber, fallSpeed, moveSpeedX);
    moveBlock(block, block->posX, block->posY);
}

void spawnWire(Wire* wire, uint16_t spriteNum, uint16_t charNumInSpritemap, uint16_t paletteNumber) {
    uint8_t startX = 84;
    uint8_t startY = 16;
    uint8_t width = 8;
    uint8_t height = 32;

    newWire(wire, startX, startY, width, height, spriteNum, charNumInSpritemap, paletteNumber);
    moveWire(wire, wire->posX, wire->posY);
}

UBYTE fallBlock(HouseBlock* block, CollisionArea* lastArea) {
    if (blocksColiding(block, lastArea)) {

        //printf("X: %u + %u >= %u && %u + %u <= %u + %u \nY: %u + %u >= %u && %u + %u <= %u + %u ", block->area->posX, block->area->width, lastArea->posX, block->area->posX, block->area->width, lastArea->posX, lastArea->width, block->area->posY, block->area->height, lastArea->posY, block->area->posY, block->area->height, lastArea->posY, lastArea->height);
        //printf("X: %u >= %u && %u <= %u + %u \nY: %u + %u >= %u && %u + %u <= %u + %u ", block->area->posX, lastArea->posX, block->area->posX, lastArea->posX, lastArea->width, block->area->posY, block->area->height, lastArea->posY, block->area->posY, block->area->height, lastArea->posY, lastArea->height);
        
        //printf("<<%u>>", (block->area->posX >= lastArea->posX && block->area->posX <= lastArea->posX + lastArea->width) && (block->area->posY >= lastArea->posY && block->area->posY <= lastArea->posY + lastArea->height));
        //printf("<<%u>>", (block->area->posX + block->area->width >= lastArea->posX && block->area->posX + block->area->width <= lastArea->posX + lastArea->width) && (block->area->posY >= lastArea->posY && block->area->posY <= lastArea->posY + lastArea->height));

        //printf(" -%u- ", lastArea->posY + lastArea->height);

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
    set_sprite_palette(4, 1, ropepalette);

    set_sprite_data(0, 16, BlockSpriteBlue);
    set_sprite_data(48, 4, Rope);

    set_bkg_palette(0, 5, BGPalette);

    set_bkg_data(0, 31, BGTiles);
    


    VBK_REG = VBK_BANK_1;
    set_bkg_tiles(0, 0, screen.width, screen.height, BGPLN1Start);

    VBK_REG = VBK_BANK_0;
    set_bkg_tiles(0, 0, screen.width, screen.height, BGPLN0Start);

    CollisionArea lastCollArea = {40, 135, 96, 16};

    HouseBlock currentBlock;
    CollisionArea area;
    spawnBlock(&currentBlock, &area, calculateMoveSpeedX(speedToBlockCount, blockCount), currentSpriteNum, 0, 0);
    currentSpriteNum++;

    HouseBlock lastBlock;
    UBYTE blocklastCollArea;

    Wire mainWire;
    spawnWire(&mainWire, 38, 48, 4);

    //HouseBlock preLastBlock;
    //UBYTE prelastCollArea;

    uint8_t i;

    //HouseBlock currentBlock;
    //CollisionArea area = {72, 50, 32, 32};
    //newBlock(&currentBlock, &area, 72, 50, 32, 32, 0, 0, 0, 0);
    //moveBlock(&currentBlock, currentBlock.posX, currentBlock.posY);

    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    while (1) {
        
        //printf("%u   %u   %u   %u   ", currentBlock.posX, currentBlock.posY, currentBlock.height, currentBlock.width);
        //printf("%u   %u   %u   %u   ", lastCollArea.posX, lastCollArea.posY, lastCollArea.height, lastCollArea.width);
        blocklastCollArea = fallBlock(&currentBlock, &lastCollArea);
        if (blocklastCollArea) {
            //printf("%u ", currentBlock.posX);
            blockCount++;
            if (currentSpriteNum == 2) startMoving = 1;
            if (currentSpriteNum == 3) movingAllowed = 1;
            if (currentSpriteNum >= 3) currentSpriteNum = 0;
            //printf("%u ", currentSpriteNum);
            if (startMoving && !movingAllowed) {
                for (i = 0; i < lastCollArea.height * 2; i++) {
                    moveScreenUp(&screen, 1);
                    renderLine(&screen);
                    currentBlock.posY += 1;
                    currentBlock.area->posY = currentBlock.posY;
                    moveBlock(&currentBlock, currentBlock.posX, currentBlock.posY);
                    lastBlock.posY += 1; 
                    lastBlock.area->posY = lastBlock.posY;
                    moveBlock(&lastBlock, lastBlock.posX, lastBlock.posY);
                    //printf("%u >>> ", lastBlock.area->posY + lastBlock.area->height);
                }
            }
            else if (startMoving && movingAllowed) {
                for (i = 0; i < lastCollArea.height; i++) {
                    moveScreenUp(&screen, 1);
                    renderLine(&screen);
                    currentBlock.posY += 1;
                    currentBlock.area->posY = currentBlock.posY;
                    moveBlock(&currentBlock, currentBlock.posX, currentBlock.posY);
                    lastBlock.posY += 1; 
                    lastBlock.area->posY = lastBlock.posY;
                    moveBlock(&lastBlock, lastBlock.posX, lastBlock.posY);
                    //printf("%u >>> ", lastBlock.area->posY + lastBlock.area->height);
                }
            }
            copyBlock(&currentBlock, &lastBlock);
            makeCollisionAreaFromBlock(&lastCollArea, &lastBlock);
            lastBlock.area = &lastCollArea;
            spawnBlock(&currentBlock, &area, calculateMoveSpeedX(speedToBlockCount, blockCount), currentSpriteNum, 0, 0);
            mainWire.posX = 84;
            mainWire.posY = 16;
            moveWire(&mainWire, mainWire.posX, mainWire.posY);
            currentSpriteNum++;
            //printf("%u ", currentSpriteNum);
        }
        if (joypad() & J_A) {
            if (currentBlock.fallSpeed == 0) {
                changeFallSpeed(&currentBlock, 1);
            }
        }

        if(currentBlock.fallSpeed == 0) {
            UBYTE blockInBorders = checkXBorders(&currentBlock);
            if (!blockInBorders) {
                currentBlock.moveSpeedX = -currentBlock.moveSpeedX;
            }
            currentBlock.posX += currentBlock.moveSpeedX;
            currentBlock.area->posX = currentBlock.posX;
            mainWire.posX += currentBlock.moveSpeedX;
            moveWire(&mainWire, mainWire.posX, mainWire. posY);
            moveBlock(&currentBlock, currentBlock.posX, currentBlock.posY);
        }

        //if (joypad() & J_UP) {
        //    moveScreenUp(&screen, 1);
        //    renderLine(&screen);
        //}

        betterDelay(1);
    }
    
}