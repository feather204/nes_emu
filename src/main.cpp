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
	std::cout << setw(40) << left << "Test 1 - LDA value: "
			  << (cpu.a == 0x42 ? "PASS" : "FAIL") << std::endl;

	// Test 2 - LDA sets zero flag
	cpu.reset();
	bus.write(0x0000, 0xA9); // lda immediate
	bus.write(0x0001, 0x00); // value 0x0
	cpu.clock();
	std::cout << setw(40) << left << "Test 2 - LDA zero flag: "
			  << (cpu.GetFlag(FLAG_ZERO) ? "PASS" : "FAIL") << std::endl;

	// Test 3 - ADC adds correctly
	cpu.reset();
	bus.write(0x0000, 0xA9); // lda immediate
	bus.write(0x0001, 0x10); // value 0x10
	bus.write(0x0002, 0x69); // ADC immediate
	bus.write(0x0003, 0x20); // value 0x20
	cpu.clock();
	cpu.clock();
	std::cout << setw(40) << left << "Test 3 - ADC Result: "
			  << (cpu.a == 0x30 ? "PASS" : "FAIL") << std::endl;

	// Test 4 - JMP sets PC
	cpu.reset();
	bus.write(0x0000, 0x4C);
	bus.write(0x0001, 0x20);
	bus.write(0x0002, 0x00);
	cpu.clock();
	std::cout << setw(40) << left << "Test 4 - JMP sets PC: "
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
	std::cout << setw(40) << left << "Test 5 - JSR/RTS returns: "
			  << (cpu.pc == 0x0003 ? "PASS" : "FAIL") << std::endl;

	// Test 6 - BEQ
	cpu.reset();
	bus.write(0x0000, 0xA9);
	bus.write(0x0001, 0x00);
	bus.write(0x0002, 0xF0);
	bus.write(0x0003, 0x0C);
	cpu.clock(); // LDA 00
	cpu.clock(); // BEQ
	std::cout << setw(40) << left << "Test 6 - BEQ branches: "
			  << (cpu.pc == 0x0010 ? "PASS" : "FAIL") << std::endl;

	// Test 7 - ASL & LSR
	cpu.reset();
	bus.write(0x0000, 0xA9);
	bus.write(0x0001, 0x81);
	bus.write(0x0002, 0x0A);
	bus.write(0x0003, 0xA9);
	bus.write(0x0004, 0x81);
	bus.write(0x0005, 0x4A);
	cpu.clock(); // LDA 81
	cpu.clock(); // ASL
	std::cout << setw(40) << left << "Test 7a - ASL results (value, carry):"
			  << (cpu.a == 0x02 ? "PASS" : "FAIL")
			  << ", " << (cpu.GetFlag(FLAG_CARRY) ? "PASS" : "FAIL") << std::endl;
	cpu.clock(); // LDA 81
	cpu.clock(); // LSR
	std::cout << setw(40) << left << "Test 7b - LSR Results (value, carry):"
			  << (cpu.a == 0x40 ? "PASS" : "FAIL")
			  << ", " << (cpu.GetFlag(FLAG_CARRY) ? "PASS" : "FAIL") << std::endl;

	// Test 8 - PHA & PLA
	cpu.reset();
	uint8_t old_sp = cpu.sp;
	bus.write(0x0000, 0xA9);
	bus.write(0x0001, 0x42);
	bus.write(0x0002, 0x48);
	bus.write(0x0003, 0xA9);
	bus.write(0x0004, 0x00);
	bus.write(0x0005, 0x68);
	cpu.clock(); // LDA 42
	cpu.clock(); // PHA
	cpu.clock(); // LDA 00
	cpu.clock(); // PLA
	std::cout << setw(40) << left << "Test 8 - PHA/PLA Results (value, sp): "
		  << (cpu.a == 0x42 ? "PASS" : "FAIL") << ", " << (cpu.sp == old_sp ? "PASS" : "FAIL") << std::endl;

	// Test 9 - PHP & PLP
	cpu.reset();
	bus.write(0x0000, 0x38);
	bus.write(0x0001, 0x78);
	bus.write(0x0002, 0x08);
	bus.write(0x0003, 0x18);
	bus.write(0x0004, 0x58);
	bus.write(0x0005, 0x28);
	cpu.clock(); // SEC
	cpu.clock(); // SEI
	uint8_t old_status = cpu.status;
	cpu.clock(); // PHP
	cpu.clock(); // CLC
	cpu.clock(); // CLI
	cpu.clock(); // PLP
	std::cout << setw(40) << left << "Test 9 - PHP/PLP Results: "
			  << ((cpu.status & ~FLAG_BREAK & ~FLAG_UNUSED) ==
			  	  (old_status & ~FLAG_BREAK & ~FLAG_UNUSED) ? "PASS" : "FAIL") << std::endl;

	return 0;
}
