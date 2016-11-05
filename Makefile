ARGS = -Wall -std=gnu11 -ggdb -O0

intel-4004:
	${CC} ${ARGS} main.c memory.c cpu.c -o 4004
