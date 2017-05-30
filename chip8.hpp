#ifndef CHIP8_H
#define CHIP8_H

#include <string>

/* Memory layout of CHIP8:

+---------------+= 0xFFF (4095) End of Chip-8 RAM
|               |
|               |
|               |
|               |
|               |
| 0x200 to 0xFFF|
|     Chip-8    |
| Program / Data|
|     Space     |
|               |
|               |
|               |
+- - - - - - - -+= 0x600 (1536) Start of ETI 660 Chip-8 programs
|               |
|               |
|               |
+---------------+= 0x200 (512) Start of most Chip-8 programs
| 0x000 to 0x1FF|
| Reserved for  |
|  interpreter  |
+---------------+= 0x000 (0) Start of Chip-8 RAM

*/

/* Unsigned char is same as one byte, used for memory. */
typedef unsigned char BYTE;

enum ERROR_CODE {
	SUCCESS,
	NO_SUCCESS,
	NOT_IMPL
};

BYTE chip8_fontset[80] =
{ 
  0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
  0x20, 0x60, 0x20, 0x20, 0x70, // 1
  0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
  0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
  0x90, 0x90, 0xF0, 0x10, 0x10, // 4
  0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
  0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
  0xF0, 0x10, 0x20, 0x40, 0x40, // 7
  0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
  0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
  0xF0, 0x90, 0xF0, 0x90, 0x90, // A
  0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
  0xF0, 0x80, 0x80, 0x80, 0xF0, // C
  0xE0, 0x90, 0x90, 0x90, 0xE0, // D
  0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
  0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

class Chip8 {

	public:
		Chip8();
		bool getDrawFlag();

		ERROR_CODE initialize();

		ERROR_CODE loadGame(std::string filepath);

		ERROR_CODE emulateCycle();

		ERROR_CODE storeKeys();

	private:
		unsigned short opcode; // 2 bytes long

		BYTE memory[4096]; // CHIP8 always has 4096 bytes of memory
		BYTE V[16]; // 16 8-bit registers, Vx where x is hexadecimal character
		
		unsigned short I; // Special 16-bit register I - used to store memory addresses
		unsigned short pc; // PC (program counter) register

		BYTE delay_timer; // Delay timer
		BYTE sound_timer; // Sound timer

		unsigned short stack[16]; // 16 layers for the stack
		unsigned short sp; // SP (stack pointer) register

		BYTE keypad[16]; // 16-key hexadecimal keypad
		BYTE display[64 * 32]; // 64 * 32 monochrome display

		bool drawFlag;
};


#endif /* CHIP8_H */