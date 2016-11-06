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

void memorySave(Memory* memory, char* filename) {
	FILE* fp = fopen(filename, "w");

	for (byte i = 0; i < memory -> maxAddress; i++) {
		fprintf(fp, "%d\n", memoryRead(memory, i));
	}

	fclose(fp);
}

void memoryLoad(Memory* memory, char* filename) {
	memoryReset(memory);

	FILE* fp = fopen(filename, "r");
	char* line = NULL;
	int val;
	size_t len = 0;

	for (int i = 0; i < memory -> maxAddress; i++) {
		if (getline(&line, &len, fp) != -1) {
			val = atoi(line);
		} else {
			val = 0;
		}

		memoryWrite(memory, i, val);
	}

	fclose(fp);
	free(line);
}
