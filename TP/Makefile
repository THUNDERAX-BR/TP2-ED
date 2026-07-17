# Compiler
CXX = g++

# Flags
CXXFLAGS = -std=c++11 -g -Wall -Iinclude

# Folders
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Target
TARGET = tp2.out

# Source files (.c, .cc, .cpp)
SRC = $(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/*.cc $(SRC_DIR)/*.cpp)

# Object files
OBJ = $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SRC))
OBJ := $(OBJ:.c=.o)
OBJ := $(OBJ:.cc=.o)
OBJ := $(OBJ:.cpp=.o)

# Default rule
all: $(BIN_DIR)/$(TARGET)

# Link
$(BIN_DIR)/$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/$(TARGET)