# Simple Makefile for the Conway's Game of Life project

# Compiler
CXX = g++
CXXFLAGS = -O3

# Target executable name
TARGET = conway

# Source files directory
SRCDIR = src
SOURCES = $(SRCDIR)/main.cpp

# Build the target executable
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# Clean the build
.PHONY: clean
clean:
	rm -f $(TARGET)

