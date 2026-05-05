/*
 * feather204
 * cpu.h
 * 5/4/2026
 *
 * CPU Class
 */

#ifndef NES_EMU_CPU_H
#define NES_EMU_CPU_H
#include "bus.h"

enum Flags {
	FLAG_CARRY			= 0b00000001,
	FLAG_ZERO			= 0b00000010,
	FLAG_INTERRUPT		= 0b00000100,
	FLAG_DECIMAL		= 0b00001000,
	FLAG_BREAK			= 0b00010000,
	FLAG_UNUSED			= 0b00100000,
	FLAG_OVERFLOW		= 0b01000000,
	FLAG_NEGATIVE		= 0b10000000,
};

class CPU {
public:
	uint8_t a = 0, x = 0, y = 0;
	uint8_t sp = 0xFD, status = 0x24;
	uint16_t lo = read(0xFFFC);
	uint16_t hi = read(0xFFFD);
	uint16_t pc = (hi << 8 | lo);

    void connectBus(Bus* b) { bus = b; }
    void reset();
    void clock();

	void SetFlag(uint8_t flag, bool value);
	bool GetFlag(uint8_t flag) const;

private:
    Bus* bus = nullptr;

    uint8_t read(uint16_t addr) const;
    void write(uint16_t addr, uint8_t data);

	void push(uint8_t data);
	uint8_t pull();

	/*
	 * Addressing modes
	 */
	uint16_t addrImplied();
	uint16_t addrAccumulator();
	uint16_t addrImmediate();
	uint16_t addrZeroPage();
	uint16_t addrZeroPageX();
	uint16_t addrZeroPageY();
	uint16_t addrAbsolute();
	uint16_t addrAbsoluteX();
	uint16_t addrAbsoluteY();
	uint16_t addrIndirect();
	uint16_t addrIndexedIndirect();
	uint16_t addrIndirectIndexed();
	uint16_t addrRelative();

	/*
	 * Instructions
	 */
	void updateZN(uint8_t result);

	void NOP();

	// Flags
	void CLC();
	void SEC();
	void CLI(); // delay by one cycle
	void SEI(); // delay by one cycle
	void CLD();
	void SED();
	void CLV();

	// Load Register
	void LDA(uint16_t addr);
	void LDX(uint16_t addr);
	void LDY(uint16_t addr);

	// Store Register
	void STA(uint16_t addr);
	void STX(uint16_t addr);
	void STY(uint16_t addr);

	// Transfers
	void TAX();
	void TXA();
	void TAY();
	void TYA();
	void TXS();
	void TSX();

	// Jumps
	void JMP(uint16_t addr);
	void JSR(uint16_t addr);
	void RTS();

	// Arithmetic
	void INX();
	void DEX();
	void INY();
	void DEY();
	void INC(uint16_t addr);
	void DEC(uint16_t addr);
	void ADC(uint16_t addr);
	void SBC(uint16_t addr);
};

#endif //NES_EMU_CPU_H