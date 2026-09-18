#ifndef TEMPAR_ADDRESS_H
#define TEMPAR_ADDRESS_H

#include <stdint.h>

static inline uint32_t tempar_real_address(uint32_t address, uint32_t address_start, uint32_t address_end) {
	address &= 0x0FFFFFFF;

	if(address <= address_end - address_start) {
		return address + address_start;
	}

	return (address > address_end ? address_end : address);
}

#endif
