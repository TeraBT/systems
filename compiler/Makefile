CC := gcc
CFLAGS := -Wall -Wextra -O2
LDFLAGS :=

TARGET := compiler

LEXER_SRCS  := lexer/lexer.c lexer/buffer.c lexer/state.c
PARSER_SRCS := parser/parser.c parser/ast.c

SRCS := $(LEXER_SRCS) $(PARSER_SRCS)
OBJS := $(SRCS:%.c=build/%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@

build/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build $(TARGET)

.PHONY: all clean
