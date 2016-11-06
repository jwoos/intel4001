#ifndef EMULATE_UTILS_H
#define EMULATE_UTILS_H

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

char getCharFromStdin();

void flush();

void printError(char*, int);

void writeStdout(char*, int);

void writeStderr(char*, int);

#endif
