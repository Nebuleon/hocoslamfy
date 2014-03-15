TARGET      ?= hocoslamfy

ifeq ($(TARGET), hocoslamfy-od)
  CC        := mipsel-linux-gcc
  STRIP     := mipsel-linux-strip
  OBJS       = platform/opendingux.o
  DEFS      := -DOPK
else
  CC        := gcc
  STRIP     := strip
  OBJS       = platform/general.o
  DEFS      := 
endif

SYSROOT     := $(shell $(CC) --print-sysroot)
SDL_CFLAGS  := $(shell $(SYSROOT)/usr/bin/sdl-config --cflags)
SDL_LIBS    := $(shell $(SYSROOT)/usr/bin/sdl-config --libs)

OBJS        += main.o init.o title.o game.o score.o audio.o bg.o text.o unifont.o
              
HEADERS     += main.h init.h platform.h title.h game.h score.h audio.h bg.h text.h unifont.h

INCLUDE     := -I.
DEFS        +=

CFLAGS       = $(SDL_CFLAGS) -Wall -Wno-unused-variable \
               -O2 -fomit-frame-pointer $(DEFS) $(INCLUDE)
LDFLAGS     := $(SDL_LIBS) -lm -lSDL_image -lSDL_mixer

include Makefile.rules

.PHONY: all opk

all: $(TARGET)

$(TARGET): $(OBJS)

opk: $(TARGET).opk

$(TARGET).opk: $(TARGET)
	$(SUM) "  OPK     $@"
	$(CMD)rm -rf .opk_data
	$(CMD)cp -r data .opk_data
	$(CMD)cp COPYRIGHT .opk_data/COPYRIGHT
	$(CMD)cp $< .opk_data/$(TARGET)
	$(CMD)$(STRIP) .opk_data/$(TARGET)
	$(CMD)mksquashfs .opk_data $@ -all-root -noappend -no-exports -no-xattrs -no-progress >/dev/null

# The two below declarations ensure that editing a .c file recompiles only that
# file, but editing a .h file recompiles everything.
# Courtesy of Maarten ter Huurne.

# Each object file depends on its corresponding source file.
$(C_OBJS): %.o: %.c

# Object files all depend on all the headers.
$(OBJS): $(HEADERS)
