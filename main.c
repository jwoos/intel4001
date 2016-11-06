#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "utils.h"
#include "memory.h"
#include "cpu.h"

int main() {
	bool debugMode = false;

	printf("Initializing memory\n");

	Memory* memory = memoryInitialize();

	printf("Memory size: %d\n\n", (int)memory->maxAddress);

	bool quitAll = false;
	char option = ' ';

	do {
		printf("1. Load default program\n");
		printf("2. Clear the memory\n");
		printf("3. Report memory\n");
		printf("D. Toggled debug settings [%s]\n", debugMode ? "true" : "false");
		printf("E. Enter program editor\n");
		printf("L. Load memory\n");
		printf("S. Save memory\n");
		printf("R. Run the current memory state through the CPU\n");
		printf("X. Exit interpter\n\n");
		printf("Selection: \n");

		option = getCharFromStdin();
		getCharFromStdin(); // hack to deal with enter
		printf("\n");

		char* input;
		size_t inputSize;

		if (!(option == 'x' || option == 'X')) {
			switch (option) {
				case '1':
					printf("Loading default machine code\n");
					// load value 1
					memoryWrite(memory, 2, 1);
					memoryWrite(memory, 3, 2);

					// load value 2
					memoryWrite(memory, 4, 2);
					memoryWrite(memory, 5, 2);

					// add
					memoryWrite(memory, 6, 3);

					// store to 12
					memoryWrite(memory, 7, 5);
					memoryWrite(memory, 8, 12);

					// print from 12
					memoryWrite(memory, 9, 6);
					memoryWrite(memory, 10, 12);

					// beep
					memoryWrite(memory, 11, 4);

					// halt
					memoryWrite(memory, 12, 0);
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

				case 'd':
				case 'D':
					debugMode = !debugMode;
					break;

				case 'e':
				case 'E':
					printf("Entering Program Editor, by memory address:\n");
					printf("N. Next address\n");
					printf("B. Previous address\n");
					printf("X. Exit editor\n");
					printf("<BYTE> changes current address and increments address\n\n");
					printf("command: \n");

					bool exitEditor = false;
					byte value;
					input = NULL;
					byte currentAddress = 2;

					do {
						printf("address: %d\n", currentAddress);

						getline(&input, &inputSize, stdin);

						if (input[0] == 'x' || input[0] == 'X') {
							exitEditor = true;
						} else if (input[0] == 'b' || input[0] == 'B') {
							if (currentAddress != 2) {
								currentAddress--;
							}
						} else if (input[0] == 'n' || input[0] == 'N') {
							currentAddress++;
						} else {
							int temp = atoi(input);
							value = (byte)temp;

							memoryWrite(memory, currentAddress, value);

							currentAddress++;
						}
						printf("address: %d\n\n", currentAddress);
					} while (!exitEditor);
					free(input);
					break;

				case 'l':
				case 'L':
					printf("Filename to load from:\n");
					input = NULL;

					// FIXME trailing newline
					getline(&input, &inputSize, stdin);

					memoryLoad(memory, input);
					free(input);
					printf("Memory loaded\n");
					break;

				case 's':
				case 'S':
					printf("Filename to save to:\n");
					input = NULL;

					// FIXME trailing newline
					getline(&input, &inputSize, stdin);

					memorySave(memory, input);
					free(input);
					printf("Memory saved\n");
					break;

				case 'r':
				case 'R':
					printf("Initializing cpu\n");
					CPU* cpu = cpuInitialize(memory, true);

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
