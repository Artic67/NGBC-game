#include <gb/gb.h>

typedef struct GameCharacter {
    UBYTE spriteIds[4];
    uint8_t xpos;
    uint8_t ypos;
    uint8_t width;
    uint8_t heigth;
} GC;
