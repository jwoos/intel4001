#include "cpu.h"

CPU* cpuInitialize(Memory* memory, bool shouldDebug) {
	CPU* cpu = malloc(sizeof(CPU));

	cpu -> memory = memory;
	cpu -> reservedAddress = 0;
	cpu -> jumpToAddress = 1;
	cpu -> baseAddress = 2;
	cpu -> addressCeiling = 253;
	cpu -> programCounter = cpu -> baseAddress;
	cpu -> register0 = 0;
	cpu -> register1 = 0;
	cpu -> overflowError = false;
	cpu -> signedMode = false;
	cpu -> halt = false;
	cpu -> debugMode = shouldDebug;

	return cpu;
}

void cpuFree(CPU* cpu) {
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
	if (cpu -> debugMode) {
		printf("CPU LOG > Halt\n");
	}

	cpu -> halt = true;
}

void cpuAdd(CPU* cpu) {
	if (cpu -> debugMode) {
		printf("CPU LOG > Add\n");
		printf("CPU LOG > Before [%d, %d]\n", cpu -> register0, cpu -> register1);
	}

	cpu -> register0 += cpu -> register1;

	if (cpu -> debugMode) {
		printf("CPU LOG > After [%d, %d]\n", cpu -> register0, cpu -> register1);
	}
}

void cpuMultiply(CPU* cpu) {
	if (cpu -> debugMode) {
		printf("CPU LOG > Multiply\n");
		printf("CPU LOG > Before [%d, %d]\n", cpu -> register0, cpu -> register1);
	}

	cpu -> register0 *= cpu -> register1;

	if (cpu -> debugMode) {
		printf("CPU LOG > After [%d, %d]\n", cpu -> register0, cpu -> register1);
	}
}

void cpuBeep(CPU* cpu) {
	if (cpu -> debugMode) {
		printf("CPU LOG > Beep\n");
	}

	printf("\a");
}

void cpuStore(CPU* cpu) {
	if (cpu -> debugMode) {
		printf("CPU LOG > Store\n");
	}

	cpu -> register1 = memoryRead(cpu -> memory, cpu -> programCounter);

	if (cpu -> debugMode) {
		printf("CPU LOG > Target address: %d\n", cpu -> register1);
		printf("CPU LOG > Value to write: %d\n", cpu -> register0);
	}

	cpu -> programCounter++;
	memoryWrite(cpu -> memory, cpu -> register1, cpu -> register0);

	if (cpu -> debugMode) {
		printf("CPU LOG > Written value: %d\n", memoryRead(cpu -> memory, cpu -> register1));
	}
}

void cpuPrint(CPU* cpu) {
	if (cpu -> debugMode) {
		printf("CPU LOG > Print\n");
	}

	cpu -> register1 = memoryRead(cpu -> memory, cpu -> programCounter);
	cpu -> programCounter++;

	cpu -> register0 = memoryRead(cpu -> memory, cpu -> register1);

	if (cpu -> debugMode) {
		printf("CPU LOG > Printing from %d, value %d\n", cpu -> register1, cpu -> register0);
	}

	printf("%d\n", (int)(cpu -> register0));
}

void cpuClearRegister0(CPU* cpu) {
	if (cpu -> debugMode) {
		printf("CPU LOG > Clear 0\n");
	}

	cpu -> register0 = 0;
}

void cpuClearRegister1(CPU* cpu) {
	if (cpu -> debugMode) {
		printf("CPU LOG > Clear 1\n");
	}

	cpu -> register1 = 0;
}

void cpuClearRegisters(CPU* cpu) {
	if (cpu -> debugMode) {
		printf("CPU LOG > Clear both\n");
	}

	cpuClearRegister0(cpu);
	cpuClearRegister1(cpu);
}

void cpuJumpTo(CPU* cpu) {
	if (cpu -> debugMode) {
		printf("CPU LOG > Jump to\n");
	}

	memoryWrite(cpu -> memory, cpu -> jumpToAddress, memoryRead(cpu -> memory, cpu -> programCounter));
	cpu -> programCounter++;

	if (cpu -> debugMode) {
		printf("Jump register set to [%d]\n", memoryRead(cpu -> memory, cpu -> jumpToAddress));
	}

	cpu -> programCounter = memoryRead(cpu -> memory, cpu -> jumpToAddress);

	if (cpu -> debugMode) {
		printf("Program counter no [%d]\n", cpu -> programCounter);
	}
}

void cpuJumpEqual(CPU* cpu) {
	if (cpu -> register0 == cpu -> register1) {
		if (cpu -> debugMode) {
			printf("CPU LOG > Jump equal\n");
		}
		cpuJumpTo(cpu);
	} else {
		if (cpu -> debugMode) {
			printf("CPU LOG > Jump equal - not jumping\n");
		}
		cpu -> programCounter++;
	}
}

void cpuCopy0(CPU* cpu) {
	if (cpu -> debugMode) {
		printf("CPU LOG > Copy 0\n");
	}

	cpu -> register1 = cpu -> register0;
}

void cpuCopy1(CPU* cpu) {
	if (cpu -> debugMode) {
		printf("CPU LOG > Copy 1\n");
	}

	cpu -> register0 = cpu -> register1;
}

void cpuLoad0(CPU* cpu) {
	if (cpu -> debugMode) {
		printf("CPU LOG > Load 0\n");
	}

	cpu -> register0 = memoryRead(cpu -> memory, cpu -> programCounter);

	if (cpu -> debugMode) {
		printf("CPU LOG > Register 0 load address [%d]\n", cpu -> register0);
	}

	cpu -> programCounter++;

	cpu -> register0 = memoryRead(cpu -> memory, cpu -> register0);

	if (cpu -> debugMode) {
		printf("CPU LOG > Register 0 [%d]\n", cpu -> register0);
	}
}

void cpuLoad1(CPU* cpu) {
	if (cpu -> debugMode) {
		printf("CPU LOG > Load 1\n");
	}

	cpu -> register1 = memoryRead(cpu -> memory, cpu -> programCounter);

	if (cpu -> debugMode) {
		printf("CPU LOG > Register 1 load address [%d]\n", cpu -> register1);
	}

	cpu -> programCounter++;

	cpu -> register1 = memoryRead(cpu -> memory, cpu -> register1);

	if (cpu -> debugMode) {
		printf("CPU LOG > Register 1 [%d]\n", cpu -> register1);
	}
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
			cpuLoad0(cpu);
			break;

		case 2:
			cpuLoad1(cpu);
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

		case 7:
			cpuClearRegister0(cpu);
			break;

		case 8:
			cpuClearRegister1(cpu);
			break;

		case 9:
			cpuJumpTo(cpu);
			break;

		case 10:
			cpuJumpEqual(cpu);
			break;

		case 11:
			cpuCopy0(cpu);
			break;

		case 12:
			cpuCopy1(cpu);
			break;

		case 13:
			cpuClearRegisters(cpu);
			break;

		case 14:
			cpuMultiply(cpu);
			break;

		default:
			printf("CPU LOG > Unknown op code - halting\n");
			cpuHalt(cpu);
	}
}

void cpuRun(CPU* cpu) {
	while (!(cpu -> halt)) {
		if (cpu -> debugMode) {
			printf("CPU LOG > Program counter [%d]\n", cpu -> programCounter);
		}

		memoryWrite(cpu -> memory, cpu -> reservedAddress, cpuFetch(cpu));
		cpuDecode(cpu, memoryRead(cpu -> memory, cpu -> reservedAddress));
	}
}
