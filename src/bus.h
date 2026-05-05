/*
 * feather204
 * bus.h
 * 5/4/2026
 *
 * Bus Class
 */

#ifndef NES_EMU_BUS_H
#define NES_EMU_BUS_H

class Bus {
public:
    uint8_t read(uint16_t addr) const;
    void write(uint16_t addr, uint8_t data);
private:
    std::array<uint8_t, 2048> ram{};
};


#endif //NES_EMU_BUS_H
