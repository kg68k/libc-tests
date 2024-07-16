# Makefile for libc-tests

ifeq ($(notdir $(CURDIR)),src)
$(error do not execute make in src directory)
endif

CC	= gcc2
CFLAGS	= -Wall -O2
MKDIR_P	= mkdir -p


.PHONY: all directories clean


TARGET = readdir.x textmode.x
GENERATED_FILES = textmode.txt

all: $(TARGET)

%.x: %.c
	$(CC) $(CFLAGS) -o $@ $^


clean:
	-rm -f $(TARGET) $(GENERATED_FILES)


# EOF
