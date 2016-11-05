#include <stdlib.h>
#include <stdio.h>

#include "memory.h"
#include "cpu.h"

int main() {
	printf("Initializing memory\n");

	Memory* memory = memoryInitialize();

	printf("Memory size: %d\n", (int)memory->maxAddress);

	printf("Loading default machine code program\n");

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

	for (byte currentAddress = 0; currentAddress < memory -> maxAddress; currentAddress++) {
		printf("memory[%d] = %d\n", currentAddress, memoryRead(memory, currentAddress));
	}

	printf("Initializing cpu\n");
	CPU* cpu = cpuInitialize(memory);

	printf("Starting...\n");
	cpuRun(cpu);
	printf("Complete\n");

	cpuFree(cpu);
}
