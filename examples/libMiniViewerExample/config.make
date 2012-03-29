# add custom variables to this file

# OF_ROOT allows to move projects outside apps/* just set this variable to the
# absoulte path to the OF root folder

OF_ROOT = ../../..


# USER_CFLAGS allows to pass custom flags to the compiler
# for example search paths like:
# USER_CFLAGS = -I src/objects

USER_CFLAGS = -I usr/local/include -I/usr/X11R6/include -I/home/walter/programmi/libMini/mini -I/home/walter/programmi/libMini/qtviewer/deps/squish -I/home/walter/programmi/libMini/qtviewer/deps/curl/include -I/home/walter/programmi/libMini/qtviewer/deps -I/home/walter/programmi/libMini/libpng

# USER_LDFLAGS allows to pass custom flags to the linker
# for example libraries like:
# USER_LD_FLAGS = libs/libawesomelib.a

USER_LDFLAGS = -L/home/walter/programmi/libMini/qtviewer/deps/squish -L/home/walter/programmi/libMini/libpng/lib/libpng15.a


# use this to add system libraries for example:
# USER_LIBS = -lpango

USER_LIBS = -lMiniSFX -lMini -lglut -L/usr/X11R6/lib -lX11 -lpthread -lcurl  -lsquish -lz -lm -ljpeg  -lOpenThreads


# change this to add different compiler optimizations to your project

USER_COMPILER_OPTIMIZATION = gcc -march=native -mtune=native -0 -Os -03 -w -Wall -Wno-parentheses -pipe --enable-shared --disable-static

EXCLUDE_FROM_SOURCE="bin,.xcodeproj,obj,.git,/usr/include/bits/termios.h"
