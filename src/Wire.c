#include <gb/gb.h>

const uint8_t tilesInWireSprite = 2;
typedef struct Wire {
    UBYTE spriteIds[2];
    uint16_t posX;
    uint16_t posY;
    uint16_t width;
    uint16_t height;
} Wire;
