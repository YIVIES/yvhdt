CC := gcc
CFLAGS := -Wall
SRC := yvhdt.c\
       output.c\
       create.c

yvhdt: $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf yvhdt
