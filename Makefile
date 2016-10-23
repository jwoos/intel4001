ARGS = -Wall -std=gnu11 -ggdb -O0

intel-4004:
	${CC} ${ARGS} 4004/main.c 4004/memory.c 4004/cpu.c -o 4004/4004
