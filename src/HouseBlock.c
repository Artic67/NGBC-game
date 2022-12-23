#include <gb/gb.h>

const uint8_t tilesInSprite = 8;
typedef struct HouseBlock {
    UBYTE spriteIds[8];
    uint8_t xpos;
    uint8_t ypos;
    uint8_t width;
    uint8_t heigth;
} HouseBlock;
