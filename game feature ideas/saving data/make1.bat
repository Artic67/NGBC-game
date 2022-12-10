mkdir build
REM c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -Wf--debug -Wl-y -c -o ./build/main.o main.c
REM c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -Wf--debug -Wl-y -o ./build/main.gb ./build/main.o

REM c:\gbdk\bin\lcc -Wa-l -c -o keyboard.o main.c
REM c:\gbdk\bin\lcc -o keyboard.gb keyboard.o

c:\gbdk\bin\lcc -Wa-l -Wf-ba0 -c -o ./build/savestate.o savestate.c
c:\gbdk\bin\lcc -Wa-l -c -o ./build/main.o main.c
c:\gbdk\bin\lcc -Wl-yt3 -Wl-yo4 -Wl-ya4 -o ./build/build.gb ./build/main.o ./build/savestate.o