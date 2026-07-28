/*
 * feather204
 * cartridge.cpp
 * 7/27/2026
 *
 * Cartridge class
 */

#include "pch.h"
#include "cartridge.h"

bool Cartridge::loadFile(const std::string& path) {
	std::ifstream file(path, std::ios::binary);

	if (!file) {
		std::cerr << "Failed to access file" << std::endl;
		return false;
	}

	uint8_t header[16];
	file.read(reinterpret_cast<char*>(header), 16);
	if (file.gcount() != 16) {
		std::cerr << "File is not the correct size" << std::endl;
		return false;
	}

	// check for iNES bytes 0-3
	if (header[0] != 0x4E || header[1] != 0x45 || header[2] != 0x53 || header[3] != 0x1A) {
		std::cerr << "Failed to validate file" << std::endl;
		return false;
	}

	// bytes 4-5
	prgBanks = header[4];
	chrBanks = header[5];

	// byte 6 (flags 6)
	nametableArrangement = header[6] & 0x01;
	hasBattery = header[6] & 0x02;
	hasTrainer = header[6] & 0x04;
	nametableAlternative = header[6] & 0x08;
	uint8_t mapperLow = (header[6] >> 4) & 0x0F;

	// byte 7 (flags 7)
	bool isNes2 = ((header[7] >> 2) & 0x03) == 2;
	uint8_t mapperUpper = (header[7] >> 4) & 0x0F;
	ramBanks = header[8];
	if (ramBanks == 0) {
		ramBanks = 1;
	}

	// ensure no junk in mapper number
	bool tailIsZero = (header[12] == 0) && (header[13] == 0) && (header[14] == 0) && (header[15] == 0);
	if (!isNes2 && !tailIsZero) {
		mapperUpper = 0;
	}

	mapperNum = (mapperUpper << 4) | mapperLow;

	// check for and read trainer
	if (hasTrainer == true) {
		uint8_t trainer[512];
		file.read(reinterpret_cast<char*>(trainer), 512);
		if (file.gcount() != 512) {
			std::cerr << "File is not the correct size" << std::endl;
			return false;
		}
	}

	// validate prg bank
	if (prgBanks == 0) {
		std::cerr << "Invalid PRG bank count" << std::endl;
		return false;
	}

	// resize and read prg bank
	size_t prgSize = prgBanks * 16384;
	prg.resize(prgSize);
	file.read(reinterpret_cast<char*>(prg.data()), prgSize);
	if (file.gcount() != static_cast<std::streamsize>(prgSize)) {
		std::cerr << "File size not expected while reading PRG-ROM" << std::endl;
		return false;
	}

	// resize and read chr bank if available
	if (chrBanks == 0) {
		chr.resize(8192);
	} else {
		size_t chrSize = chrBanks * 8192;
		chr.resize(chrSize);
		file.read(reinterpret_cast<char*>(chr.data()), chrSize);
		if (file.gcount() != static_cast<std::streamsize>(chrSize)) {
			std::cerr << "File size not expected while reading CHR-ROM" << std::endl;
			return false;
		}
	}

	if (mapperNum != 0) {
		std::cerr << "Unsupported mapper number" << std::endl;
	}

	return true;
}

uint8_t Cartridge::cpuRead(uint16_t addr) {
	return false;
}

void Cartridge::cpuWrite(uint16_t addr, uint8_t data) {
	return false;
}