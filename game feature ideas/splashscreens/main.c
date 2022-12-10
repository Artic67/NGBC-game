#include <stdio.h>
#include <gb/gb.h>
#include "bulb_data.c"
#include "bulb_map.c"

void main() {

    set_bkg_data(0, 206, bulb_data);
    set_bkg_tiles(0, 0, 20, 18, bulb_map);

    SHOW_BKG;
    DISPLAY_ON;

    waitpad(J_START);

    printf("Start of game");
    

}