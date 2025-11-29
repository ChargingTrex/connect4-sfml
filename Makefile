# Connect4 SFML Makefile
# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system

# Target executable
TARGET = connect4_sfml

# Source files
SOURCES = connect4_sfml.cpp animation.cpp popup.cpp start_screen.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Header dependencies
HEADERS = animation.h popup.h start_screen.h

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo "Build complete! Run with: ./$(TARGET)"

# Compile source files to object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "Clean complete!"

# Rebuild from scratch
rebuild: clean all

# Run the game
run: $(TARGET)
	./$(TARGET)

# Phony targets (not actual files)
.PHONY: all clean rebuild run
