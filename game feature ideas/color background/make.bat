mkdir build

c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -c -o ./build/Map.o Map.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -c -o ./build/MapSprites.o MapSprites.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -c -o ./build/main.o main.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -Wl-yp0x143=0x80 -o ./build/main.gb ./build/Map.o ./build/MapSprites.o ./build/main.o

DEL .\build\*.lst
DEL .\build\*.o
DEL .\build\*.map
DEL .\build\*.sym