#include <stdint.h>
#include <stdio.h>

#include "address.h"

static int failures;

static void expect(const char *name, uint32_t got, uint32_t want) {
	if(got != want) {
		printf("FAIL %s: got 0x%08X, want 0x%08X\n", name, got, want);
		failures++;
	}
}

int main(void) {
	const uint32_t start = 0x08800000;
	const uint32_t end = 0x09FFFFFF;

	expect("relative base", tempar_real_address(0, start, end), start);
	expect("relative offset", tempar_real_address(0x10000, start, end), 0x08810000);
	expect("relative max", tempar_real_address(end - start, start, end), end);
	expect("absolute address", tempar_real_address(0x08802000, start, end), 0x08802000);
	expect("flagged address", tempar_real_address(0xF8802000, start, end), 0x08802000);
	expect("out of range", tempar_real_address(0x0A000000, start, end), end);

	if(failures) {
		printf("%d address test(s) failed\n", failures);
		return 1;
	}

	puts("address tests passed");
	return 0;
}
