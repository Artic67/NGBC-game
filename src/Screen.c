#include <gb/gb.h>

typedef struct Screen
{
    int16_t width;
    int16_t height;
    int16_t posX;
    int16_t posY;
    int16_t lastRendered;
    int8_t lastTile;
} Screen;
