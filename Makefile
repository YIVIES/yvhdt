CC := gcc
CFLAGS := -Wall -g
SRC := yvhdt.c

yvhdt: $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf yvhdt
