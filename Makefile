CXX      := clang++
CXXFLAGS := -std=c++20 -Wall -Wextra -O3
INCS     := -I/opt/homebrew/include
LIBS     := -L/opt/homebrew/lib -lglfw
FRAMEWORKS := -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

all: main

main: main.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS) $(FRAMEWORKS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $(INCS) -c $< -o $@

clean:
	rm -f main.o main
.PHONY: all clean
