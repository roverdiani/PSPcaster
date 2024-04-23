TARGET = PSPcaster
OBJS := $(patsubst src/%.cpp,src/%.o,$(wildcard src/*.cpp))

CXXFLAGS = -std=c++17 -fno-rtti

LIBS = -lstdc++ -lSDL2 -lGL -lpspvram -lpspaudio -lpspvfpu -lpsphprm -lpspgu -lpng -ljpeg -lz -lpspdebug -lpspdisplay -lpspge -lpspctrl -lpspnet -lpspnet_apctl

# PSP Stuff
PSP_FW_VERSION = 500
BUILD_PRX = 1

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = PSPcaster

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

# Debug target
debug: CFLAGS += -g3 -DDEBUG -O0
debug: all