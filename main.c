#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "utils.h"
#include "memory.h"
#include "cpu.h"

int main() {
	printf("Initializing memory\n");

	Memory* memory = memoryInitialize();

	printf("Memory size: %d\n\n", (int)memory->maxAddress);

	bool quitAll = false;
	char option = ' ';

	do {
		printf("1. Load Default Program\n");
		printf("2. Clear the Memory\n");
		printf("3. Report Memory\n");
		printf("R. Run the current memory state through the CPU\n");
		printf("X. Exit Interpter\n\n");
		printf("Selection: \n");

		option = getCharFromStdin();
		getCharFromStdin(); // hack to deal with enter
		printf("\n");

		if (!(option == 'x' || option == 'X')) {
			switch (option) {
				case '1':
					printf("Loading default machine code\n");
					// load value 1
					memoryWrite(memory, 1, 1);
					memoryWrite(memory, 2, 1);

					// load value 2
					memoryWrite(memory, 3, 2);
					memoryWrite(memory, 4, 2);

					// add
					memoryWrite(memory, 5, 3);

					// store to 12
					memoryWrite(memory, 6, 5);
					memoryWrite(memory, 7, 12);

					// print from 12
					memoryWrite(memory, 8, 6);
					memoryWrite(memory, 9, 12);

					// beep
					memoryWrite(memory, 10, 4);

					// half
					memoryWrite(memory, 11, 0);
					break;
				case '2':
					printf("Resetting memory");
					memoryReset(memory);
					break;
				case '3':
					for (byte currentAddress = 0; currentAddress < memory -> maxAddress; currentAddress++) {
						printf("memory[%d] = %d\n", currentAddress, memoryRead(memory, currentAddress));
					}
					break;
				case 'r':
				case 'R':
					printf("Initializing cpu\n");
					CPU* cpu = cpuInitialize(memory);

					printf("Starting...\n");
					cpuRun(cpu);
					printf("Complete\n");

					cpuFree(cpu);
					break;
				default:
					printf("Not a valid option");
			}
		} else {
			quitAll = true;
		}
		printf("\n\n\n");
	} while (!quitAll);

	memoryFree(memory);
}
