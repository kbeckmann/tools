CC=gcc
CFLAGS=
LDFLAGS=-z execstack
SOURCES=exec_shellcode.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=exec_shellcode

all: $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)

