/*
 * feather204
 * cpu_instructions.cpp
 * 5/5/2026
 *
 * Handle CPU Instructions
 */

#include "pch.h"
#include "cpu.h"

/**
 * Update FLAG_ZERO and FLAG_NEGATIVE
 * @param result Value to compare
 */
void CPU::updateZN(uint8_t result) {
	SetFlag(FLAG_ZERO, result == 0);
	SetFlag(FLAG_NEGATIVE, result & 0x80);
}

/**
 * No Operation
 */
void CPU::NOP() {
}

/**
 * Clear FLAG_CARRY
 */
void CPU::CLC() {
	SetFlag(FLAG_CARRY, false);
}

/**
 * Set FLAG_CARRY
 */
void CPU::SEC() {
	SetFlag(FLAG_CARRY, true);
}

/**
 * Clear FLAG_INTERRUPT
 */
void CPU::CLI() {
	SetFlag(FLAG_INTERRUPT, false);
}

/**
 * Set FLAG_INTERRUPT
 */
void CPU::SEI() {
	SetFlag(FLAG_INTERRUPT, true);
}

/**
 * Clear FLAG_DECIMAL
 */
void CPU::CLD() {
	SetFlag(FLAG_DECIMAL, false);
}

/**
 * Set FLAG_DECIMAL
 */
void CPU::SED() {
	SetFlag(FLAG_DECIMAL, true);
}

/**
 * Clear FLAG_OVERFLOW
 */
void CPU::CLV() {
	SetFlag(FLAG_OVERFLOW, false);
}

/**
 * Load A from memory.
 * @param addr Address
 */
void CPU::LDA(uint16_t addr) {
	a = read(addr);
	updateZN(a);
}

/**
 * Load X from memory.
 * @param addr Address
 */
void CPU::LDX(uint16_t addr) {
	x = read(addr);
	updateZN(x);
}

/**
 * Load Y from memory.
 * @param addr Address
 */
void CPU::LDY(uint16_t addr) {
	y = read(addr);
	updateZN(y);
}

/**
 * Store A into memory.
 * @param addr Address
 */
void CPU::STA(uint16_t addr) {
	write(addr, a);
}

/**
 * Store X into memory.
 * @param addr Address
 */
void CPU::STX(uint16_t addr) {
	write(addr, x);
}

/**
 * Store Y into memory.
 * @param addr Address
 */
void CPU::STY(uint16_t addr) {
	write(addr, y);
}

/**
 * Transfer A to X.
 * Update Flags
 */
void CPU::TAX() {
	x = a;
	updateZN(x);
}

/**
 * Transfer X to A.
 * Update Flags
 */
void CPU::TXA() {
	a = x;
	updateZN(a);
}

/**
 * Transfer A to Y.
 * Update Flags
 */
void CPU::TAY() {
	y = a;
	updateZN(y);
}

/**
 * Transfer Y to A.
 * Update Flags
 */
void CPU::TYA() {
	a = y;
	updateZN(a);
}

/**
 * Transfer X to SP.
 */
void CPU::TXS() {
	sp = x;
}

/**
 * Transfer SP to X.
 * Update Flags
 */
void CPU::TSX() {
	x = sp;
	updateZN(x);
}

/**
 * Jump PC to an address.
 * @param addr Address
 */
void CPU::JMP(uint16_t addr) {
	pc = addr;
}

/**
 * Jump to Subroutine.
 * @param addr Address
 */
void CPU::JSR(uint16_t addr) {
	uint16_t returnAddr = pc - 1;
	push(returnAddr >> 8);
	push(returnAddr & 0xFF);
	pc = addr;
}

/**
 * Return from Subroutine.
 */
void CPU::RTS() {
	uint8_t lo = pull();
	uint8_t hi = pull();
	pc = hi << 8 | lo;
	pc++;
}

/**
 * Increment X register.
 */
void CPU::INX() {
	x++;
	updateZN(x);
}

/**
 * Increment Y register.
 */
void CPU::INY() {
	y++;
	updateZN(y);
}

/**
 * Decrement X register.
 */
void CPU::DEX() {
	x--;
	updateZN(x);
}

/**
 * Decrement Y register.
 */
void CPU::DEY() {
	y--;
	updateZN(y);
}

/**
 * Increment the memory value.
 * @param addr Address
 */
void CPU::INC(uint16_t addr) {
	uint8_t mem = read(addr);
	mem++;
	write(addr, mem);
	updateZN(mem);
}

/**
 * Decrement the memory value.
 * @param addr Address
 */
void CPU::DEC(uint16_t addr) {
	uint8_t mem = read(addr);
	mem--;
	write(addr, mem);
	updateZN(mem);
}

/**
 * Add with carry.
 * @param addr Address
 */
void CPU::ADC(uint16_t addr) {
	uint8_t mem = read(addr);
	uint16_t result = a + mem + GetFlag(FLAG_CARRY);
	SetFlag(FLAG_CARRY, result > 0xFF);
	SetFlag(FLAG_OVERFLOW, (result ^ a) & (result ^ mem) & 0x80);
	a = result & 0xFF;
	updateZN(a);
}

/**
 * Subtract with carry.
 * @param addr Address
 */
void CPU::SBC(uint16_t addr) {
	uint8_t mem = ~read(addr);
	uint16_t result = a + mem + GetFlag(FLAG_CARRY);
	SetFlag(FLAG_CARRY, result > 0xFF);
	SetFlag(FLAG_OVERFLOW, (result ^ a) & (result ^ ~mem) & 0x80);
	a = result & 0xFF;
	updateZN(a);
}