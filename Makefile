CC := gcc
CFLAGS := -Wall
SRC := yvhdt.c

yvhdt: $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf yvhdt
