#include "chip8.hpp"
#include <stdio.h>
#include <stdlib.h>

Chip8::Chip8 () {}

bool Chip8::getDrawFlag()
{
	return this->drawFlag;
}

ERROR_CODE Chip8::initialize()
{
	this->drawFlag = false;
	this->pc = 0x200; // programs always start at 0x200
	this->I = 0;
	this->sp = 0;

	// clear display
	for(int i = 0; i < 64 * 32; i++){
		this->display[i] = 0;
	}

	// clear stack & registers & keypad
	for(int i = 0; i < 16; i++){
		this->stack[i] = 0;
		this->V[i] = 0;
		this->keypad[i] = 0;
	}

	// clear memory
	for(int i = 0; i < 4096; i++){
		this->memory[i] = 0;
	}

	for(int i = 0; i < 80; i++){
		this->memory[i] = chip8_fontset[i];
	}

	// reset timers
	this->delay_timer = 0;
	this->sound_timer = 0;

	return SUCCESS;
}

ERROR_CODE Chip8::loadGame(std::string filepath)
{
	FILE *pFile;
	pFile = fopen(filepath.c_str(), "rb");
	if(pFile != NULL){
		long lSize;
		fseek(pFile, 0, SEEK_END);
		lSize = ftell(pFile);
		rewind(pFile);

		char *buffer = (char *) malloc(sizeof(char) * lSize);
		if(buffer == NULL) return NO_SUCCESS;

		size_t result = fread(buffer, 1, lSize, pFile);
		if(lSize != result) return NO_SUCCESS;

		for(int i = 0; i < lSize; i++){
			this->memory[512 + i] = buffer[i];
		}

		fclose(pFile);
		free(buffer);
		return SUCCESS;
	} else {
		return NO_SUCCESS;
	}
}

ERROR_CODE Chip8::emulateCycle() 
{
	// first fetch opcode
	this->opcode = memory[pc] << 8 | memory[pc + 1];

	switch(this->opcode & 0xF000)
	{
		case 0x0000:
			switch(this->opcode & 0x000F)
			{
				case 0x0000: // Clear the display
					for(int i = 0; i < 64* 32; i++)
						this->display[i] = 0;
					this->pc += 2;
					break;

				case 0x000E: // Return from subroutine
					if(this->sp > 0 && this->sp < 17){
						this->pc = this->stack[this->sp - 1];
						this->sp--;
					}
			}
			break;

		case 0x1000: // 1nnnn - JP addr -> jump to location nnn
			this->pc = this->opcode & 0x0FFF;

		case 0x2000: // 2nnn -> call subroutine at nnn
			this->stack[this->sp] = this->pc;
			this->sp++;
			this->pc = this->opcode & 0x0FFF;

		case 0x3000: // 3xkk -> skip next instr if Vx = kk
			this->pc += 2;
			if(this->V[(this->opcode >> 8) & 0x0F] == (this->opcode & 0x00FF))
				this->pc += 2;

		case 0x4000: // 4xkk -> skip next instr if Vx != kk
			this->pc += 2;
			if(this->V[(this->opcode >> 8) & 0x0F] !=  (this->opcode & 0x00FF))
				this->pc += 2;

		case 0x5000: // 5xy0 -> skip next instr if Vx = Vy
			this->pc += 2;
			if(this->V[(this->opcode >> 8) & 0x0F] == this->V[(this->opcode >> 4) & 0x00F])
				this->pc += 2;

		case 0x6000: // 6xkk -> set Vx = kk
			this->pc += 2;
			this->V[(this->opcode >> 8) & 0x0F] = this->opcode & 0x00FF;

		case 0x7000:

		case 0x8000:

		case 0x9000:

		case 0xA000: // Annn -> sets I = nnn
			this->I = this->opcode & 0x0FFF;
			this->pc += 2;
			break;

		case 0xB000:

		case 0xC000:

		case 0xD000:

		case 0xE000:

		case 0xF000:

		default:
			printf("Unknown opcode: 0x%X\n", this->opcode);
	}

	return NOT_IMPL;
}

ERROR_CODE Chip8::storeKeys()
{
	return NOT_IMPL;
}