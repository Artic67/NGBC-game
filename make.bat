mkdir build
c:\gbdk\bin\lcc -c -o ./build/BGTiles.o ./src/BGTiles.c
c:\gbdk\bin\lcc -c -o ./build/BG.o ./src/BG.c
c:\gbdk\bin\lcc -c -o ./build/BlockSpriteBlue.o ./src/BlockSpriteBlue.c
c:\gbdk\bin\lcc -c -o ./build/main.o main.c
c:\gbdk\bin\lcc -Wl-yp0x143=0x80 -o ./build/main.gb ./build/BlockSpriteBlue.o ./build/BG.o ./build/BGTiles.o ./build/main.o

DEL .\build\*.lst
DEL .\build\*.o
DEL .\build\*.map
DEL .\build\*.sym