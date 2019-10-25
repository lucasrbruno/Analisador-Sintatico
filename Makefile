CC = gcc
CFLAGS = -g -Wall
CLIBS = -lm
OBJS = io.o
TARGET = sintatico
all: $(TARGET)

sintatico: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o teste0 sintatico.c $(CLIBS)

io.o: io.c 
	$(CC) $(CFLAGS) -c io.c $(CLIBS)

clean:
	rm -rf $(OBJS) token.txt sintatico