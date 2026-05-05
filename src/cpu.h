/*
 * feather204
 * CPU Class
 */

#ifndef NES_EMU_CPU_H
#define NES_EMU_CPU_H

class Bus;

class CPU {
public:
    void connectBus(Bus* b);
    void reset();
    void clock();

private:
    uint8_t a = 0, x = 0, y = 0;
    uint8_t sp = 0, status = 0;
    uint16_t pc = 0;

    Bus* bus = nullptr;

    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t data);
};

#endif //NES_EMU_CPU_H