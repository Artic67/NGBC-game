if "%~1"=="" goto end

set path="%1\bin\lcc"

mkdir build

%path% -c -o ./build/WindowMap.o ./src/WindowMap.c
%path% -c -o ./build/Rope.o ./src/Rope.c
%path% -c -o ./build/BGTiles.o ./src/BGTiles.c
%path% -c -o ./build/BGWOffset.o ./src/BGWOffset.c
%path% -c -o ./build/BlockSpriteBlue.o ./src/BlockSpriteBlue.c
%path% -c -o ./build/main.o main.c

%path% -Wl-yp0x143=0x80 -o ./build/main.gb ./build/BlockSpriteBlue.o ./build/BGWOffset.o ./build/BGTiles.o ./build/Rope.o ./build/WindowMap.o ./build/main.o

DEL .\build\*.lst
DEL .\build\*.o
DEL .\build\*.map
DEL .\build\*.sym

:end