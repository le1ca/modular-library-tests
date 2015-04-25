CC?=gcc
CCFLAGS?=-Wall -Werror -g
LDFLAGS?=
TARGET=../mod-test

SOURCES?=$(wildcard *.c)
OBJECTS?=$(SOURCES:.c=.o)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

%.o: %.c %.h
	$(CC) $(CCFLAGS) -c -o $@ $<
	
%.o: %.c
	$(CC) $(CCFLAGS) -c -o $@ $<
	
clean:
	rm -f $(OBJECTS) $(TARGET) 
