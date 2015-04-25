CC?=gcc
MODULE_INCS?=$(shell find ../modules/ -type d -not -wholename '../modules/' | awk '{print "-I" $$0}')
CCFLAGS?=-Wall -Werror -g $(MODULE_INCS)
LDFLAGS?=-ldl
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
