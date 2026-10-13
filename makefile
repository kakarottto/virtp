CC := g++
SRC_DIR := ./src
INC_DIR := ./include
BUILD_DIR := build
SRCS := $(shell find $(SRC_DIR) -type f -name "*.cpp")
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
CFLAGS := -I$(INC_DIR) -Wall -Wextra -O2
LDLIBS := -lSDL3 -lSDL3_image -lSDL3_ttf -lcurl
TARGET := windy

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDLIBS)

# compile each source file
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean
