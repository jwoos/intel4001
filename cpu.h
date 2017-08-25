#ifndef CPU_4001_CPU
#define CPU_4001_CPU

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "memory.h"

typedef struct CPU {
	Memory* memory;
	byte reservedAddress;
	byte baseAddress;
	byte jumpToAddress;
	byte addressCeiling;
	byte programCounter;
	byte register0;
	byte register1;
	bool overflowError;
	bool underflowError;
	bool signedMode;
	bool halt;
	bool debugMode;
} CPU;

CPU* cpuInitialize(Memory*, bool);

void cpuFree(CPU*);

void cpuReset(CPU*);

byte cpuFetch(CPU*);

void cpuHalt(CPU*);

void cpuAdd(CPU*);

void cpuMultiply(CPU*);

void cpuBeep(CPU*);

void cpuStore(CPU*);

void cpuPrint(CPU*);

void cpuDecode(CPU*, byte);

void cpuRun(CPU*);

void cpuClearRegister0(CPU*);

void cpuClearRegister1(CPU*);

void cpuClearRegisters(CPU*);

void cpuJumpTo(CPU*);

void cpuJumpEqual(CPU*);

void cpuCopy0(CPU*);

void cpuCopy1(CPU*);

void cpuLog(CPU*, char*);

void cpuLoad0(CPU*);

void cpuLoad1(CPU*);

#endif
