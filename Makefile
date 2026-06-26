CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -Isrc -g
LDFLAGS :=
BUILD := build

SRCS := \
	src/main.c \
	src/core/cpu.c \
	src/core/cpu_ops.c \
	src/core/cpu_addr.c \
	src/core/cpu_tables.c \
	src/core/bus.c \

OBJS := $(SRCS:%.c=$(BUILD)/%.o)

.PHONY: all clean test

all: $(BUILD)/nes

$(BUILD)/nes: $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD)