#ifndef CPU_4001_UTILS
#define CPU_4001_UTILS

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

char getCharFromStdin();

void flush();

void printError(char*, int);

void writeStdout(char*, int);

void writeStderr(char*, int);

#endif
