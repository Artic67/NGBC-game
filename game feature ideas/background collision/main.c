#include <gb/gb.h>
#include <stdio.h>
#include "Character.c"
#include "Map.c"
#include "MapTiles.c"

uint8_t playerlocation[2];
const char blankTile[1] = {0x00};
const char keyTile = 0x02;
const char doorTile = 0x03;
UBYTE debug, hasKey, gameRunning;

void betterDelay(uint8_t numloops) {
    uint8_t i;
    for(i = 0; i < numloops; i++) {
        wait_vbl_done();
    }
}

UBYTE canPlayerMove(uint8_t newplayerx, uint8_t newplayery) {
    uint16_t indexTopLeftX, indexTopLeftY, tileIndexTopLeft;
    UBYTE result;
    
    indexTopLeftX = (newplayerx - 8) / 8;
    indexTopLeftY = (newplayery - 16) / 8;
    tileIndexTopLeft = 20 * indexTopLeftY + indexTopLeftX;

    if (debug == 1) {
        printf("%u %u\n", (uint16_t)(newplayerx), (uint16_t)(newplayery));
        printf("%u %u %u    \n", (uint16_t)(indexTopLeftX), (uint16_t)(indexTopLeftY), (uint16_t)(tileIndexTopLeft));
    }

    result = Map[tileIndexTopLeft] == blankTile[0];

    if (Map[tileIndexTopLeft] == keyTile) {
        //collect key
        set_bkg_tiles(indexTopLeftX, indexTopLeftY, 1, 1, blankTile);
        hasKey = 1;
        result = 1;
    } else if (hasKey == 1 && Map[tileIndexTopLeft] == doorTile) {
        //open door
        set_bkg_tiles(indexTopLeftX, indexTopLeftY, 1, 1, blankTile);
        result = 1;
    } else if (indexTopLeftX == 20) {
        //end game
        gameRunning = 0;
        HIDE_SPRITES;
        printf("\n \n \n \n \n \n \n \n \n      YOU WIN!");
        result = 1;
    }

    return result;
}

void animateSprite(uint8_t spriteIndex, int8_t moveX, int8_t moveY) {
    while(moveX != 0) {
        scroll_sprite(spriteIndex, moveX < 0 ? -1 : 1, 0);
        moveX += (moveX < 0 ? 1 : -1);
        wait_vbl_done();
    }

    while(moveY != 0) {
        scroll_sprite(spriteIndex, 0, moveY < 0 ? -1 : 1);
        moveY += (moveY < 0 ? 1 : -1);
        wait_vbl_done();
    }
}

void main() {

    set_sprite_data(0, 1, Character);
    set_sprite_tile(0, 0);

    set_bkg_data(0, 4, MapTiles);
    set_bkg_tiles(0, 0, 20, 18, Map);

    playerlocation[0] = 16;
    playerlocation[1] = 24;

    move_sprite(0, playerlocation[0], playerlocation[1]);

    gameRunning = 1;

    SHOW_SPRITES;
    SHOW_BKG;
    DISPLAY_ON;

    while(gameRunning == 1) {

        if (joypad() & J_A) {
            debug = 1;
        }

        if (joypad() & J_LEFT && canPlayerMove(playerlocation[0] - 8, playerlocation[1])) {
            playerlocation[0] -= 8;
            animateSprite(0, -8, 0);
        }
        if (joypad() & J_RIGHT && canPlayerMove(playerlocation[0] + 8, playerlocation[1])) {
            playerlocation[0] += 8;
            animateSprite(0, 8, 0);
        }
        if (joypad() & J_UP && canPlayerMove(playerlocation[0], playerlocation[1] - 8)) {
            playerlocation[1] -= 8;
            animateSprite(0, 0, -8);
        }
        if (joypad() & J_DOWN && canPlayerMove(playerlocation[0], playerlocation[1] + 8)) {
            playerlocation[1] += 8;
            animateSprite(0, 0, 8);
        }
        betterDelay(6);
    }
}