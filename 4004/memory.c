#include "memory.h"

Memory* memoryInitialize() {
	Memory* memory = malloc(sizeof(Memory));
	memory -> maxAddress = 255;
	memory -> memorySpace = calloc(1, sizeof(byte) * 255);

	return memory;
}

void memoryReset(Memory* memory) {
	for (int i = 0; i < memory -> maxAddress; i++) {
		memory -> memorySpace[i] = 0;
	}
}

byte memoryRead(Memory* memory, byte address) {
	return memory -> memorySpace[address];
}

void memoryWrite(Memory* memory, byte address, byte value) {
	memory -> memorySpace[address] = value;
}

void memoryFree(Memory* memory) {
	free(memory -> memorySpace);
	free(memory);
}
