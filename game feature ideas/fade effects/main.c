#include <stdio.h>
#include <gb/gb.h>
#include "bulb_data.c"
#include "bulb_map.c"
#include "MapTiles.c"
#include "Map.c"

uint8_t i;

void betterDelay(uint8_t numloops) {
    uint8_t i;
    for(i = 0; i < numloops; i++) {
        wait_vbl_done();
    }

}

void fadeOut() {
    for (i = 0; i < 4; i++) {
        switch (i) {
            case 0:
                BGP_REG = 0xE4;
                break;
            case 1:
                BGP_REG = 0xF9;
                break;
            case 2:
                BGP_REG = 0xFE;
                break;
            case 3:
                BGP_REG = 0xFF;
                break;
            }
        betterDelay(5);
    }
}

void fadeIn() {
    for (i = 0; i < 3; i++) {
        switch (i) {
            case 0:
                BGP_REG = 0xFE;
                break;
            case 1:
                BGP_REG = 0xF9;
                break;
            case 2:
                BGP_REG = 0xE4;
                break;
            }
        betterDelay(5);
    }
}

void main() {

    set_bkg_data(0, 206, bulb_data);
    set_bkg_tiles(0, 0, 20, 18, bulb_map);

    SHOW_BKG;
    DISPLAY_ON;

    waitpad(J_START);

    fadeOut();

    set_bkg_data(0, 4, MapTiles);
    set_bkg_tiles(0, 0, 20, 18, Map);

    fadeIn();
}