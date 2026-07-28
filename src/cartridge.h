/*
 * feather204
 * cartridge.h
 * 7/27/2026
 * 
 * Cartridge class
 */

#ifndef NES_EMU_CARTRIDGE_H
#define NES_EMU_CARTRIDGE_H


class Cartridge {
public:
	bool loadFile(const std::string& path);
	uint8_t cpuRead(uint16_t addr);
	void cpuWrite(uint16_t addr, uint8_t data);
private:
	std::vector<uint8_t> prg;
	std::vector<uint8_t> chr;
	uint8_t mapperNum = 0;
	uint8_t prgBanks = 1, chrBanks = 1;
	bool nametableArrangement = false;
	bool nametableAlternative = false;
	bool hasTrainer = false;
	bool hasBattery = false;
	uint8_t ramBanks = 1;
};


#endif //NES_EMU_CARTRIDGE_H
