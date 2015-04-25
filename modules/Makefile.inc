CC?=gcc
CCFLAGS?=-Wall -Werror -g -fPIC
LDFLAGS?=-shared

SOURCES?=$(wildcard *.c)
OBJECTS?=$(SOURCES:.c=.o)

../$(MODULE).so: $(OBJECTS)
	$(CC) -o ../$(MODULE).so $(OBJECTS) $(LDFLAGS)

%.o: %.c %.h
	$(CC) $(CCFLAGS) -c -o $@ $<
	
%.o: %.c
	$(CC) $(CCFLAGS) -c -o $@ $<
	
clean:
	rm -f $(OBJECTS) $(MODULE).so
