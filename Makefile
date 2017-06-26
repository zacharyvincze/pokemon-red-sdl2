CXX ?= g++-5.2
MKDIR := mkdir -p
CXXFLAGS += `pkg-config --cflags sdl2 SDL2_image SDL2_ttf`
CXXFLAGS += -pedantic -std=c++11
LDFLAGS += `pkg-config --libs sdl2 SDL2_image SDL2_ttf`
PROG := bin/pokemon
OBJS := $(patsubst src/%.cpp,obj/%.o, $(wildcard src/*.cpp))
OBJS += $(patsubst src/data/maps/%.cpp,obj/data/maps/%.o, $(wildcard src/data/maps/*.cpp))
OBJS += $(patsubst src/constants/%.cpp,obj/constants/%.o, $(wildcard src/constants/*.cpp))
OBJS += $(patsubst src/data/%.cpp,obj/data/%.o, $(wildcard src/data/*.cpp))
DEPS := $(OBJS:.o=.d)

.PHONY: all clean

all: build

build: $(PROG)

-include $(DEPS)

clean:
	rm -rf $(PROG) $(OBJS)

$(PROG): $(OBJS)
		@$(MKDIR) $(dir $@)
		$(CXX) $^ $(CXXFLAGS) $(LDFLAGS) -o $@

obj/%.o : src/%.cpp
		@$(MKDIR) $(dir $@)
		$(CXX) $< $(CXXFLAGS) -c -MD -o $@

run: bin/./pokemon
