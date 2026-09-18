CC ?= cc
CFLAGS ?= -O2 -Wall -Wextra -Werror

TESTS := test_address

.PHONY: all run clean

all: $(TESTS)

test_address: test_address.c ../src/include/address.h
	$(CC) $(CFLAGS) -I../src/include -o $@ test_address.c

run: all
	./test_address

clean:
	rm -f $(TESTS)
