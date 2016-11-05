#include "cpu.h"

CPU* cpuInitialize(Memory* memory) {
	CPU* cpu = malloc(sizeof(CPU));

	cpu -> memory = memory;
	cpu -> reservedAddress = 0;
	cpu -> baseAddress = 1;
	cpu -> addressCeiling = 253;
	cpu -> programCounter = cpu -> baseAddress;
	cpu -> register0 = 0;
	cpu -> register1 = 0;
	cpu -> overflowError = false;
	cpu -> overflowError = false;
	cpu -> signedMode = false;
	cpu -> halt = false;

	return cpu;
}

void cpuFree(CPU* cpu) {
	memoryFree(cpu -> memory);
	free(cpu);
}

void cpuReset(CPU* cpu) {
	cpu -> halt = false;
	cpu -> programCounter = cpu -> baseAddress;
	cpu -> overflowError = false;
	cpu -> underflowError = false;
	cpu -> signedMode = false;
}

byte cpuFetch(CPU* cpu) {
	byte opCode = 0;
	opCode = memoryRead(cpu -> memory, cpu -> programCounter);
	cpu -> programCounter++;

	if (cpu -> programCounter > cpu -> addressCeiling) {
		cpuHalt(cpu);
	}

	return opCode;
}

void cpuHalt(CPU* cpu) {
	cpu -> halt = true;
}

void cpuAdd(CPU* cpu) {
	cpu -> register0 += cpu -> register1;
}

void cpuBeep(CPU* cpu) {
	printf("\a");
}

void cpuStore(CPU* cpu) {
	cpu -> register1 = memoryRead(cpu -> memory, cpu -> programCounter);
	cpu -> programCounter++;
	memoryWrite(cpu -> memory, cpu -> register1, cpu -> register0);
}

void cpuPrint(CPU* cpu) {
	cpu -> register1 = memoryRead(cpu -> memory, cpu -> programCounter);
	cpu -> programCounter++;

	cpu -> register0 = memoryRead(cpu -> memory, cpu -> register1);

	printf("%d\n", (int)(cpu -> register0));
}

void cpuDecode(CPU* cpu, byte opCode) {
	if (cpu -> halt) {
		return;
	}

	switch (opCode) {
		case 0:
			cpuHalt(cpu);
			break;
		case 1:
			cpu -> register0 = memoryRead(cpu -> memory, cpu -> programCounter);
			cpu -> programCounter++;
			break;
		case 2:
			cpu -> register1 = memoryRead(cpu -> memory, cpu -> programCounter);
			cpu -> programCounter++;
			break;
		case 3:
			cpuAdd(cpu);
			break;
		case 4:
			cpuBeep(cpu);
			break;
		case 5:
			cpuStore(cpu);
			break;
		case 6:
			cpuPrint(cpu);
			break;
	}
}

void cpuRun(CPU* cpu) {
	while (!(cpu -> halt)) {
		memoryWrite(cpu -> memory, cpu -> reservedAddress, cpuFetch(cpu));
		cpuDecode(cpu, memoryRead(cpu -> memory, cpu -> reservedAddress));
	}
}
