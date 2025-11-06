CXX := clang++
CXXFLAGS := -std=c++20 -Wall -Wextra -O3 -I/opt/homebrew/include
LDFLAGS := -L/opt/homebrew/lib
LDLIBS := -lglfw
FRAMEWORKS := -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

SRC := $(wildcard *.cpp)

all: main

main: $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS) $(FRAMEWORKS)

clean:
	rm -f main

.PHONY: all clean
