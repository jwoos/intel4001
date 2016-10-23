#ifndef CPU_4004_CPU
#define CPU_4004_CPU

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "memory.h"

typedef struct CPU {
	Memory* memory;
	byte reservedAddress;
	byte baseAddress;
	byte addressCeiling;
	byte programCounter;
	byte register0;
	byte register1;
	bool overflowError;
	bool underflowError;
	bool signedMode;
	bool halt;
} CPU;

CPU* cpuInitialize(Memory*);

void cpuFree(CPU*);

void cpuReset(CPU*);

byte cpuFetch(CPU*);

void cpuHalt(CPU*);

void cpuAdd(CPU*);

void cpuBeep(CPU*);

void cpuStore(CPU*);

void cpuPrint(CPU*);

void cpuDecode(CPU*, byte);

void cpuRun(CPU*);

#endif
