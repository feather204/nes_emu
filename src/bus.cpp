/*
 * feather204
 * bus.cpp
 * 5/4/2026
 *
 * Bus Class
 */

#include "pch.h"
#include "bus.h"

uint8_t Bus::read(uint16_t addr) const {
	// RAM ($0000 to $1FFF) (mirroring)
	if (addr <= 0x1fff) {
		return ram[addr & 0x07FF];
	}

	// PPU Registers ($2000 to $3FFF)
	if (addr <= 0x3FFF) {
		return 0x00;
	}

	// APU/IO Registers ($4000 to $401F)
	if (addr <= 0x401F) {
		return 0x00;
	}

	// Cartridge ROM ($8000 to $FFFF)
	if (addr <= 0xFFFF) {
		return 0x00;
	}

	return 0x00;
}

void Bus::write(uint16_t addr, uint8_t data) {
	// RAM ($0000 to $1FFF) (mirroring)
	if (addr <= 0x1FFF) {
		ram[addr & 0x07FF] = data;
	}

	// PPU ($2000 to $3FFF)
	if (addr <= 0x3FFF) {

	}

	// APU/IO ($4000 to $401F)
	if (addr <= 0x401F) {

	}
}