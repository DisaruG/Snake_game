CC = gcc
CFLAGS = -Wall -Wextra -std=c89
LDFLAGS =

SRC_DIR = src
BUILD_DIR = build

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

EXECUTABLE = eat

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
    $(CC) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
    $(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
    mkdir -p $@

clean:
    rm -rf $(BUILD_DIR) $(EXECUTABLE)
