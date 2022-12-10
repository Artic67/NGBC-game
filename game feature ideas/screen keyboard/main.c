#include <stdio.h>
#include <gb/gb.h>
#include "Keyboard.c"
#include "KeyTiles.c"
#include "CursorSprite.c"
#include "Cursor.c"

typedef const struct CursorStats {
    const uint8_t minx;
    const uint8_t miny;
    const uint8_t maxx;
    const uint8_t maxy;
} CursorStats;

Cursor cursor;
CursorStats cursorStats = {12, 80, 156, 128};
UBYTE keyDown;
uint8_t nameCharacterIndex = 0;
unsigned char playerName[18];
UBYTE playerHasName = 0;

void betterDelay(uint8_t numloops) {
    uint8_t i;
    for(i = 0; i < numloops; i++) {
        wait_vbl_done();
    }

}

UBYTE isInKeyboard(uint8_t x, uint8_t y) {
    if (x==140 && y==144 || x==156 && y==144) {
        return 1;
    }
    return x >= cursorStats.minx && x <= cursorStats.maxx && y >= cursorStats.miny && y <= cursorStats.maxy;
}

void addCharToName(Cursor* cursor) {
    uint16_t characterIndex = 160 + 2 * cursor->row * 20 + 2 * cursor->col;


    if (nameCharacterIndex == 18) return;
    if (characterIndex == 1) {}
    playerName[nameCharacterIndex] = Keyboard[characterIndex];
    if (playerName[nameCharacterIndex] == 0x00) {}
    //printf("%u %u %u %u \n", playerName[0], playerName[1], playerName[2], playerName[3]);
    nameCharacterIndex++;
}

void removeFromPlayerName() {
    if (nameCharacterIndex > 0) {
        nameCharacterIndex--;
        playerName[nameCharacterIndex] = 0;
    }
}

void drawPlayerName() {
    set_bkg_tiles(1, 5, 18, 1, playerName);
}

void updatePlayerName(Cursor* cursor) {
    if (cursor->col == 8 && cursor->row == 4) {
        // delete char
        removeFromPlayerName();
        drawPlayerName();
    } else if (cursor->col == 9 && cursor->row == 4) {
        // enter name
        playerHasName = 1;
    } else {
        // add char to name
        addCharToName(cursor);
        drawPlayerName();
    }
}


void main() {

    set_sprite_data(0, 1, CursorSprite);
    set_sprite_tile(0, 0);

    cursor.xpos = 12;
    cursor.ypos = 80;
    cursor.col = 0;
    cursor.row = 0;
    move_sprite(0, cursor.xpos, cursor.ypos);

    set_bkg_data(0, 45, KeyTiles);
    set_bkg_tiles(0, 0, 20, 18, Keyboard);
    scroll_bkg(-4, 0);

    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;
    
    while (!playerHasName) {

        if (keyDown == 1) {
            waitpadup();
            keyDown = 0;
        } 

        switch (joypad()) {
            case J_UP:
                if (isInKeyboard(cursor.xpos, cursor.ypos - 16)) {
                    cursor.ypos -= 16;
                    cursor.row--;
                    scroll_sprite(0, 0, -16);
                    keyDown = 1;
                }
                break;
            case J_DOWN:
                if (isInKeyboard(cursor.xpos, cursor.ypos + 16)) {
                    cursor.ypos += 16;
                    cursor.row++;
                    scroll_sprite(0, 0, 16);
                    keyDown = 1;
                }
                break;
            case J_LEFT:
                if (isInKeyboard(cursor.xpos - 16, cursor.ypos)) {
                    cursor.xpos -= 16;
                    cursor.col--;
                    scroll_sprite(0, -16, 0);
                    keyDown = 1;
                }
                break;
            case J_RIGHT:
                if (isInKeyboard(cursor.xpos + 16, cursor.ypos)) {
                    cursor.xpos += 16;
                    cursor.col++;
                    scroll_sprite(0, 16, 0);
                    keyDown = 1;
                }
                break;
            case J_A:
                updatePlayerName(&cursor);
                keyDown = 1;
                break;
        }
        betterDelay(2);
    }

}