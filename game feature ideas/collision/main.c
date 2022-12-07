#include <gb/gb.h>
#include <stdio.h>
#include "GameCharacter.c"
#include "GameSprites.c"

GC han;
GC vamp;
UBYTE spriteSize = 8;

UBYTE checkCollision(GC* one, GC* two) {
    return (one->xpos >= two->xpos && one->xpos <= two->xpos + two->width) && (one->ypos >= two->ypos && one->ypos <= two->ypos + two->heigth) || (two->xpos >= one->xpos && two->xpos <= one->xpos + one->width) && (two->ypos >= one->ypos && two->ypos <= one->ypos + one->heigth);
}

void moveGameCharacter(GC* character, uint8_t x, uint8_t y) {
    move_sprite(character -> spriteIds[0], x, y);
    move_sprite(character -> spriteIds[1], x + spriteSize, y);
    move_sprite(character -> spriteIds[2], x, y + spriteSize);
    move_sprite(character -> spriteIds[3], x + spriteSize, y + spriteSize);
}

void setupCharacter(GC* character, uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t charNumInSpritemap) {
    character -> xpos = x;
    character -> ypos = y;
    character -> width = width;
    character -> heigth = height;

    for(uint8_t i = 0; i < 4; i++) {
        set_sprite_tile(charNumInSpritemap * 4 + i, charNumInSpritemap * 4 + i);
        character -> spriteIds[i] = charNumInSpritemap * 4 + i;
    }
}

void betterDelay(uint8_t numloops) {
    uint8_t i;
    for(i = 0; i < numloops; i++) {
        wait_vbl_done();
    }
}

void main() {

    set_sprite_data(0, 8, GameSprites);

    setupCharacter(&han, 80, 130, 16, 16, 0);
    setupCharacter(&vamp, 30, 50, 16, 16, 1);

    moveGameCharacter(&han, han.xpos, han.ypos);
    moveGameCharacter(&vamp, vamp.xpos, vamp.ypos);

    SHOW_SPRITES;
    DISPLAY_ON;

    while (!checkCollision(&han, &vamp)) {
        if (joypad() & J_LEFT) {
            han.xpos -= 2;
            moveGameCharacter(&han, han.xpos, han.ypos);
        }
        if (joypad() & J_RIGHT) {
            han.xpos += 2;
            moveGameCharacter(&han, han.xpos, han.ypos);
        }

        vamp.ypos += 4;

        if (vamp.ypos >= 150) {
            vamp.ypos = 0;
            vamp.xpos = han.xpos;
        }

        moveGameCharacter(&vamp, vamp.xpos, vamp.ypos);

        betterDelay(3);
    }
    
    printf("\n \n \n \n \n \n \n ==- GAME OVER -==");

}