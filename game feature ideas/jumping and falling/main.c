#include <stdio.h>
#include <gb/gb.h>
#include "bg.c"
#include "tilemap.c"
#include "FaceSprites.c"

uint8_t playerStats[4] = {10, 135, 3, 0};
uint8_t characterNum = 0;
uint8_t jumping = 0;
uint8_t acceleration = 0;
uint8_t gravity = 2;
uint8_t floorYpos = 135;

void betterDelay(uint8_t numloops) {
    uint8_t i;
    for(i = 0; i < numloops; i++) {
        wait_vbl_done();
    }

}

int8_t collisionDetect(uint8_t projectedYpos) {
    if (projectedYpos > floorYpos) {
        return 1;
    }
    return -1;
}

void jump(uint8_t characterNum, uint8_t charStats[4]) {
    
    if (!jumping) {
        jumping = 1;
        charStats[3] = 15;
    }

    charStats[3] = charStats[3] - gravity;
    
    charStats[1] = charStats[1] - charStats[3];

    if  (collisionDetect(charStats[1]) == 1) {
        jumping = 0;
        charStats[3] = 0;
        charStats[1] = floorYpos;
    }

    move_sprite(characterNum, charStats[0], charStats[1]);
    
}

void main() {

    set_sprite_data(0, 2, Face);

    set_bkg_data(0, 8, Tilemap);
    set_bkg_tiles(0, 0, 40, 18, bg);

    set_sprite_tile(characterNum, 0);
    move_sprite(characterNum, playerStats[0], playerStats[1]);

    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    while (1) {
        if (joypad()) {
            
            if (joypad() & J_LEFT) {
                acceleration = -playerStats[2];
            } else if (joypad() & J_RIGHT) {
                acceleration = playerStats[2];
            }
            playerStats[0] = playerStats[0] + acceleration;
            move_sprite(characterNum, playerStats[0], playerStats[1]);
            
        }

        if (joypad() & J_A || jumping == 1) {
            jump(characterNum, playerStats);
            
        }
        betterDelay(2);
        acceleration = 0;
    }

}