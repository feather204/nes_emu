/*
 * feather204
 * cpu_addressing.cpp
 * 5/5/2026
 *
 * Handle CPU Addressing
 */

#include "cpu.h"

/**
 * Zero Page Indexed X
 * d, x
 */
uint16_t CPU::addrZeroPageX() {
	return (read(pc++) + x) & 0xFF;
}

/**
 * Zero Page Indexed Y
 * d, y
 */
uint16_t CPU::addrZeroPageY() {
	return (read(pc++) + y) & 0xFF;
}

/**
 * Absolute Indexed X
 * a, x
 */
uint16_t CPU::addrAbsoluteX() {
	uint16_t lo = read(pc++);
	uint16_t hi = read(pc++);
	return (hi << 8 | lo) + x;
}

/**
 * Absolute Indexed Y
 * a, y
 */
uint16_t CPU::addrAbsoluteY() {
	uint16_t lo = read(pc++);
	uint16_t hi = read(pc++);
	return (hi << 8 | lo) + y;
}

/**
 * Indexed Indirect X
 * (d, x)
 */
uint16_t CPU::addrIndexedIndirect(){
	uint8_t arg = read(pc++);
	uint8_t ptr = (arg + x) & 0xFF;
	uint16_t lo = read(ptr);
	uint16_t hi = read((ptr + 1) & 0xFF);
	return hi << 8 | lo;
}

/**
 * Indirect Indexed Y
 * (d), y
 */
uint16_t CPU::addrIndirectIndexed() {
	uint8_t arg = read(pc++);
	uint16_t lo = read(arg);
	uint16_t hi = read((arg + 1) & 0xFF);
	return (hi << 8 | lo) + y;
}

/**
 * Implicit
 */
uint16_t CPU::addrImplied() {
	return 0;
}

/**
 * Accumulator
 */
uint16_t CPU::addrAccumulator() {
	return 0;
}

/**
 * Immediate
 */
uint16_t CPU::addrImmediate() {
	return pc++;
}

/**
 * Zero Page
 */
uint16_t CPU::addrZeroPage() {
	return read(pc++);
}

/**
 * Absolute
 */
uint16_t CPU::addrAbsolute() {
	uint16_t lo = read(pc++);
	uint16_t hi = read(pc++);
	return (hi << 8) | lo;
}

/**
 * Relative
 */
uint16_t CPU::addrRelative() {
	auto offset = (int8_t)read(pc++);
	return pc + offset;
}

/**
 * Indirect
 */
uint16_t CPU::addrIndirect() {
	uint16_t lo = read(pc++);
	uint16_t hi = read(pc++);
	uint16_t ptr = (hi << 8) | lo;
	return (read(ptr + 1) << 8) | read(ptr);
}