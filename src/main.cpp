/*
 * feather204
 * main.cpp
 * 5/4/2026
 *
 * Main Class
 */

#include "pch.h"
#include "cpu.h"
#include "bus.h"

using namespace std;

int main() {
	CPU cpu;
	Bus bus;
	cpu.connectBus(&bus);

	// Test 1 - LDA loads immediate value
	cpu.reset();
	bus.write(0x0000, 0xA9);
	bus.write(0x0001, 0x42);
	cpu.clock();
	std::cout << setw(30) << left << "Test 1 - LDA value: "
			  << (cpu.a == 0x42 ? "PASS" : "FAIL") << std::endl;

	// Test 2 - LDA sets zero flag
	cpu.reset();
	bus.write(0x0000, 0xA9); // lda immediate
	bus.write(0x0001, 0x0); // value 0x10
	cpu.clock();
	std::cout << setw(30) << left << "Test 2 - LDA zero flag: "
			  << (cpu.GetFlag(FLAG_ZERO) ? "PASS" : "FAIL") << std::endl;

	// Test 3 - ADC adds correctly
	cpu.reset();
	bus.write(0x0000, 0xA9); // lda immediate
	bus.write(0x0001, 0x10); // value 0x10
	bus.write(0x0002, 0x69); // ADC immediate
	bus.write(0x0003, 0x20); // value 0x20
	cpu.clock();
	cpu.clock();
	std::cout << setw(30) << left << "Test 3 - ADC Result: "
			  << (cpu.a == 0x30 ? "PASS" : "FAIL") << std::endl;

	// Test 4 - JMP sets PC
	cpu.reset();
	bus.write(0x0000, 0x4C);
	bus.write(0x0001, 0x20);
	bus.write(0x0002, 0x00);
	cpu.clock();
	std::cout << setw(30) << left << "Test 4 - JMP sets PC: "
			  << (cpu.pc == 0x0020 ? "PASS" : "FAIL") << std::endl;

	// Test 5 - JSR and RTS
	cpu.reset();
	bus.write(0x0000, 0x20);
	bus.write(0x0001, 0x10);
	bus.write(0x0002, 0x00);
	bus.write(0x0010, 0xEA);
	bus.write(0x0011, 0x60);
	cpu.clock(); // JSR
	cpu.clock(); // NOP
	cpu.clock(); // RTS
	std::cout << setw(30) << left << "Test 5 - JSR/RTS returns: "
			  << (cpu.pc == 0x0003 ? "PASS" : "FAIL") << std::endl;

	return 0;
}
