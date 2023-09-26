CC := gcc
CFLAGS := -Wall -ggdb
SRC := yvhdt.c\
       output.c\
       create.c

yvhdt: $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf yvhdt
