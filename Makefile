# 	g++ -c main.cpp Game.cpp Ball.cpp Cannon.cpp -I "D:\SFML\64\SFML-2.6.1-mingw-64-bit\SFML-2.6.1\include" 
# 	g++ main.o Game.o Cannon.o Ball.o -o ice -L "D:\SFML\64\SFML-2.6.1-mingw-64-bit\SFML-2.6.1\lib" -lsfml-graphics -lsfml-window -lsfml-system


CXX := g++
CXXFLAGS := -std=c++17 -Wall -I"D:\SFML\64\SFML-2.6.1-mingw-64-bit\SFML-2.6.1\include" -O2 -Wno-switch
LDFLAGS := -L"D:\SFML\64\SFML-2.6.1-mingw-64-bit\SFML-2.6.1\lib" -lsfml-graphics -lsfml-window -lsfml-system

# Define the source, build, and binary directory
SRCDIR := src
BUILDDIR := build
BINDIR := bin

# Automatically list all the C++ source files
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
# Convert the list of source files into a list of corresponding object files
OBJECTS := $(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(SOURCES:.cpp=.o))

# Define the target executable
TARGET := $(BINDIR)/ice

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "Linking..."
	@mkdir -p $(BINDIR)
	$(CXX) $^ -o $@ $(LDFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@echo "Cleaning..."
	@rm -rf $(BUILDDIR) $(BINDIR)

# Non-file targets
.PHONY: all clean
