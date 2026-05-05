/*
 * feather204
 * Bus Class
 */

#ifndef NES_EMU_BUS_H
#define NES_EMU_BUS_H

class Bus {
public:
    uint8_t read(uint8_t addr);
    void write(uint8_t addr, uint8_t data);
private:
    std::array<uint8_t, 2048> ram{};
};


#endif //NES_EMU_BUS_H
