CXX = g++
CXX_FLAGS = -std=c++20 -Wall -Wextra -O3
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Target executable name
TARGET = geometry-wars

# Directories
BUILD_DIR = build

# Source files
SRCS = main.cpp Vec2.cpp Entity.cpp EntityManager.cpp Game.cpp
# Components.hpp is a header-only component in this structure, but we include it in dependencies
HEADERS = Vec2.hpp Entity.hpp EntityManager.hpp Game.hpp Components.hpp

# Object files
OBJS = $(addprefix $(BUILD_DIR)/, $(SRCS:.cpp=.o))

# Default rule
all: $(TARGET)

# Link the target
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile source files to object files
$(BUILD_DIR)/%.o: %.cpp $(HEADERS) | $(BUILD_DIR)
	$(CXX) $(CXX_FLAGS) -c $< -o $@

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean rule
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean
