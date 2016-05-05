CC := gcc
SOURCE := $(wildcard *.c)
OBJECT := $(patsubst %.c,%.bin,$(SOURCE))

all: $(OBJECT)

clean: 
	@rm -f $(OBJECT)
%.bin:  %.c
	$(CC) -Wall $< -o $@

