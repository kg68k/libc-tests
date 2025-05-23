# Makefile for libc-tests

ifeq ($(notdir $(CURDIR)),src)
$(error do not execute make in src directory)
endif

CC	= gcc2
CFLAGS	= -Wall -O2
MKDIR_P	= mkdir -p


.PHONY: all directories clean


TARGET = readdir.x textmode.x textmode2.x textmode3.x envp.x
GENERATED_FILES = textmode.txt test2.txt test3.txt

all: $(TARGET)

%.x: %.c
	$(CC) $(CFLAGS) -o $@ $^


clean:
	-rm -f $(TARGET) $(GENERATED_FILES)


# EOF
