CC = cc
CFLAGS = -std=c23 -Wall -Wextra -Wpedantic

TARGET = lexer
OBJS = lexer.o token_def.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(TARGET) $(OBJS)
