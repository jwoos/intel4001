ARGS = -Wall -std=gnu11 -ggdb -O0

intel-4001:
	${CC} ${ARGS} main.c memory.c cpu.c utils.c -o 4001
