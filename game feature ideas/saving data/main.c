#include <stdio.h>
#include <gb/gb.h>
#include "Keyboard.c"
#include "KeyTiles.c"
#include "CursorSprite.c"
#include "Cursor.c"
#include "Welcome.c"

typedef const struct CursorStats {
    const uint8_t minx;
    const uint8_t miny;
    const uint8_t maxx;
    const uint8_t maxy;
} CursorStats;

extern uint8_t playerName[18];
uint8_t playerNameNotSaved[18];
Cursor cursor;
CursorStats cursorStats = {12, 80, 156, 128};
UBYTE keyDown;
uint8_t nameCharacterIndex = 0, i;
UBYTE playerHasName = 0;

void betterDelay(uint8_t numloops) {
    uint8_t ii;
    for(i = 0; ii < numloops; ii++) {
        wait_vbl_done();
    }

}

void saveNameToMBC() {
    for (i=0; i<18; i++) {
        playerName[i] = playerNameNotSaved[i];
    }
}

void loadNameFromMBC() {
    for (i=0; i<18; i++) {
        playerNameNotSaved[i] = playerName[i];
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
    playerNameNotSaved[nameCharacterIndex] = Keyboard[characterIndex];
    if (playerNameNotSaved[nameCharacterIndex] == 0x00) {}
    //printf("%u %u %u %u \n", playerNameNotSaved[0], playerNameNotSaved[1], playerNameNotSaved[2], playerNameNotSaved[3]);
    nameCharacterIndex++;
}

void removeFromplayerNameNotSaved() {
    if (nameCharacterIndex > 0) {
        nameCharacterIndex--;
        playerNameNotSaved[nameCharacterIndex] = 0;
    }
}

void drawPlayerName() {
    set_bkg_tiles(1, 5, 18, 1, playerNameNotSaved);
}

void updateplayerNameNotSaved(Cursor* cursor) {
    if (cursor->col == 8 && cursor->row == 4) {
        // delete char
        removeFromplayerNameNotSaved();
        drawPlayerName();
    } else if (cursor->col == 9 && cursor->row == 4) {
        // enter name
        playerHasName = 1;
        saveNameToMBC();
    } else {
        // add char to name
        addCharToName(cursor);
        drawPlayerName();
    }
}

void resetName() {
    for (i=0; i!=18; i++) {
        playerNameNotSaved[i] = 0x00;
    }
    playerHasName = 0;
}

void sayWelcomeScreen() {
    set_bkg_data(0, 45, KeyTiles);

    set_bkg_tiles(0, 0, 20, 18, Welcome);

    drawPlayerName();

    SHOW_BKG;
    HIDE_SPRITES;
    DISPLAY_ON;
}

void askForNameScreen() {
    resetName();
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
                updateplayerNameNotSaved(&cursor);
                keyDown = 1;
                break;
        }
        betterDelay(2);
    }

    scroll_bkg(4, 0);
    return;
}

void main() {
    ENABLE_RAM_MBC1;

    if(playerName[0] > 0x2C) {
        askForNameScreen();
    }
    
    loadNameFromMBC();
    sayWelcomeScreen();

    DISABLE_RAM_MBC1;
}