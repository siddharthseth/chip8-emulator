#include "chip8.hpp"
#include <iostream>

Chip8 myChip8;

int main(int argc, char **argv)
{
	// setupGraphics();
	// setupInput();

	myChip8.initialize();
	myChip8.loadGame("games/PONG");

	for(;;)
	{
		myChip8.emulateCycle();

		if(myChip8.getDrawFlag())
		{
			//drawGraphics(&myChip8);
		}

		myChip8.storeKeys();
	}

	return 0;
}