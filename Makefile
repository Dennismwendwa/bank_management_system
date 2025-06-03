V ?= 0
ifeq ($(V),1)
    Q =
else
    Q = @
endif

# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -std=c++17 -Iinclude
CXXFLAGS += -Wall -Wextra -Wuninitialized -Wmaybe-uninitialized
CXXFLAGS += -g -O0
CXXFLAGS += -MMD -MP

# folders
SRC_DIR := src
OBJ_DIR := build
BIN_DIR := bin
TARGET := $(BIN_DIR)/bank_app

# find all source files
SRCS := $(shell find $(SRC_DIR) -name '*.cpp')
# Convert .cpp paths to .o paths in build/
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o,$(SRCS))
# Dependency files for rebuild checks
DEPS := $(OBJS:.o=.d)

# Default rule
all: $(TARGET)

# Link object files to create the binary
# -lbcrypt
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJS) -o $@ -lpqxx -lpq
	@echo "##Build complete: $@"

# Compile each .cpp to .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	$(Q)rm -rf $(OBJ_DIR) $(BIN_DIR)
	$(Q)echo "Cleaned build and bin directories."

# Include dependency files if they exist
-include $(DEPS)

run: bin/bank_app
	./bin/bank_app