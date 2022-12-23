mkdir build
c:\gbdk\bin\lcc -c -o ./build/BlockSpriteBlue.o ./src/BlockSpriteBlue.c
c:\gbdk\bin\lcc -c -o ./build/main.o main.c
c:\gbdk\bin\lcc -Wl-yp0x143=0x80 -o ./build/main.gb ./build/BlockSpriteBlue.o ./build/main.o