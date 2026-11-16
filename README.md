# NES Emulator

A Nintendo Entertainment System emulator written from scratch in C for Linux.

The 6502 processor, the picture processing unit, the cartridge interface and the bus connecting them are each implemented directly from hardware documentation and verified against test ROMs as well as actual games.

# Building
Requires SDL3.

    make
    ./build/nes [path to ROM.nes]

note: no ROMs are included in this project 

# Status

### CPU: 
Complete: All 56 official opcodes, all 12 addressing modes, interrupts

Todo: Unofficial opcodes

### Memory and cartridge:
Complete: Functional bus, mapper interface, NROM (mapper 0)

Todo: Other mappers

### PPU:
Complete: Tile decoding, register interface, clock, vblank, NMI, Background rendering

Todo: scrolling, foreground rendering (sprites) 

### Other:
Complete: SDL3 video frontend

Todo: Controller input, APU (audio), save states

# Attribution
Hardware behavior referenced from the [NESdev Wiki](https://www.nesdev.org/wiki/)
Opcode table and NTSC palette values adapted from [olcNES](https://github.com/OneLoneCoder/olcNES)