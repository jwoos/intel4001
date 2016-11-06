#ifndef CPU_4004_MEMORY
#define CPU_4004_MEMORY

#include <stdlib.h>
#include <stdio.h>

typedef unsigned char byte;

typedef struct Memory {
	byte maxAddress;
	byte* memorySpace;
} Memory;

Memory* memoryInitialize();

void memoryReset(Memory*);

byte memoryRead(Memory*, byte);

void memoryWrite(Memory*, byte, byte);

void memoryFree(Memory*);

void memorySave(Memory*, char*);

void memoryLoad(Memory*, char*);

#endif
