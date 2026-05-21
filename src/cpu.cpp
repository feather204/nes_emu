/*
 * feather204
 * cpu.cpp
 * 5/4/2026
 *
 * CPU Class
 */


#include "pch.h"
#include "cpu.h"

/**
 * Reset for CPU
 */
void CPU::reset() {
	a = 0;
	x = 0;
	y = 0;
	sp = 0xFD;
	status = 0x24;
	uint16_t lo = read(0xFFFC);
	uint16_t hi = read(0xFFFD);
	pc = (hi << 8 | lo);
}

/**
 * Clock cycle for CPU
 */
void CPU::clock() {
	uint8_t opcode = read(pc++);
	switch (opcode) {
		case 0xEA: NOP(); break;

		case 0x18: CLC(); break;
		case 0x38: SEC(); break;
		case 0x58: CLI(); break;
		case 0x78: SEI(); break;
		case 0xD8: CLD(); break;
		case 0xF8: SED(); break;
		case 0xB8: CLV(); break;

		case 0xA9: LDA(addrImmediate()); break;
		case 0xA5: LDA(addrZeroPage()); break;
		case 0xB5: LDA(addrZeroPageX()); break;
		case 0xAD: LDA(addrAbsolute()); break;
		case 0xBD: LDA(addrAbsoluteX()); break;
		case 0xB9: LDA(addrAbsoluteY()); break;
		case 0xA1: LDA(addrIndexedIndirect()); break;
		case 0xB1: LDA(addrIndirectIndexed()); break;

		case 0xA2: LDX(addrImmediate()); break;
		case 0xA6: LDX(addrZeroPage()); break;
		case 0xB6: LDX(addrZeroPageY()); break;
		case 0xAE: LDX(addrAbsolute()); break;
		case 0xBE: LDX(addrAbsoluteY()); break;

		case 0xA0: LDY(addrImmediate()); break;
		case 0xA4: LDY(addrZeroPage()); break;
		case 0xB4: LDY(addrZeroPageX()); break;
		case 0xAC: LDY(addrAbsolute()); break;
		case 0xBC: LDY(addrAbsoluteX()); break;

		case 0x85: STA(addrZeroPage()); break;
		case 0x95: STA(addrZeroPageX()); break;
		case 0x8D: STA(addrAbsolute()); break;
		case 0x9D: STA(addrAbsoluteX()); break;
		case 0x99: STA(addrAbsoluteY()); break;
		case 0x81: STA(addrIndexedIndirect()); break;
		case 0x91: STA(addrIndirectIndexed()); break;

		case 0x86: STX(addrZeroPage()); break;
		case 0x96: STX(addrZeroPageY()); break;
		case 0x8E: STX(addrAbsolute()); break;

		case 0x84: STY(addrZeroPage()); break;
		case 0x94: STY(addrZeroPageX()); break;
		case 0x8C: STY(addrAbsolute()); break;

		case 0xAA: TAX(); break;
		case 0x8A: TXA(); break;
		case 0xA8: TAY(); break;
		case 0x98: TYA(); break;
		case 0x9A: TXS(); break;
		case 0xBA: TSX(); break;

		case 0x4C: JMP(addrAbsolute()); break;
		case 0x6C: JMP(addrIndirect()); break;

		case 0x20: JSR(addrAbsolute()); break;

		case 0x60: RTS(); break;

		case 0xE8: INX(); break;
		case 0xCA: DEX(); break;
		case 0xC8: INY(); break;
		case 0x88: DEY(); break;

		case 0xE6: INC(addrZeroPage()); break;
		case 0xF6: INC(addrZeroPageX()); break;
		case 0xEE: INC(addrAbsolute()); break;
		case 0xFE: INC(addrAbsoluteX()); break;

		case 0xC6: DEC(addrZeroPage()); break;
		case 0xD6: DEC(addrZeroPageX()); break;
		case 0xCE: DEC(addrAbsolute()); break;
		case 0xDE: DEC(addrAbsoluteX()); break;

		case 0x69: ADC(addrImmediate()); break;
		case 0x65: ADC(addrZeroPage()); break;
		case 0x75: ADC(addrZeroPageX()); break;
		case 0x6D: ADC(addrAbsolute()); break;
		case 0x7D: ADC(addrAbsoluteX()); break;
		case 0x79: ADC(addrAbsoluteY()); break;
		case 0x61: ADC(addrIndexedIndirect()); break;
		case 0x71: ADC(addrIndirectIndexed()); break;

		case 0xE9: SBC(addrImmediate()); break;
		case 0xE5: SBC(addrZeroPage()); break;
		case 0xF5: SBC(addrZeroPageX()); break;
		case 0xED: SBC(addrAbsolute()); break;
		case 0xFD: SBC(addrAbsoluteX()); break;
		case 0xF9: SBC(addrAbsoluteY()); break;
		case 0xE1: SBC(addrIndexedIndirect()); break;
		case 0xF1: SBC(addrIndirectIndexed()); break;

		case 0x90: BCC(addrRelative()); break;
		case 0xB0: BCS(addrRelative()); break;
		case 0xF0: BEQ(addrRelative()); break;
		case 0x30: BMI(addrRelative()); break;
		case 0xD0: BNE(addrRelative()); break;
		case 0x10: BPL(addrRelative()); break;
		case 0x50: BVC(addrRelative()); break;
		case 0x70: BVS(addrRelative()); break;

		case 0xC9: CMP(addrImmediate()); break;
		case 0xC5: CMP(addrZeroPage()); break;
		case 0xD5: CMP(addrZeroPageX()); break;
		case 0xCD: CMP(addrAbsolute()); break;
		case 0xDD: CMP(addrAbsoluteX()); break;
		case 0xD9: CMP(addrAbsoluteY()); break;
		case 0xC1: CMP(addrIndexedIndirect()); break;
		case 0xD1: CMP(addrIndirectIndexed()); break;

		case 0xE0: CPX(addrImmediate()); break;
		case 0xE4: CPX(addrZeroPage()); break;
		case 0xEC: CPX(addrAbsolute()); break;

		case 0xC0: CPY(addrImmediate()); break;
		case 0xC4: CPY(addrZeroPage()); break;
		case 0xCC: CPY(addrAbsolute()); break;

		default: break;
	}
}

/**
 * Read from the bus
 * @param addr Address
 * @return Value from memory
 */
uint8_t CPU::read(uint16_t addr) const {
	return bus->read(addr);
}

/**
 * Write to the bus
 * @param addr Address
 * @param data Data to write
 */
void CPU::write(uint16_t addr, uint8_t data) {
	bus->write(addr, data);
}

/**
 * Set a flag value
 * @param flag Flag to set
 * @param value Value to set to
 */
void CPU::SetFlag(uint8_t flag, bool value) {
	if (value)
		status |= flag;
	else
		status &= ~flag;
}

/**
 * Get a flag value
 * @param flag Flag to get
 * @return Flag value
 */
bool CPU::GetFlag(uint8_t flag) const {
	return (status & flag) != 0;
}

/**
 * Pull data from stack
 * @return Value from stack
 */
uint8_t CPU::pull() {
	sp++;
	uint16_t addr = 0x0100 + sp;
	return read(addr);
}

/**
 * Push data to stack
 * @param data Data to push
 */
void CPU::push(uint8_t data) {
	uint16_t addr = 0x0100 + sp;
	write(addr, data);
	sp--;
}