#include "utils.h"

char getCharFromStdin() {
	char buffer[1];

	int bytesRead = read(STDIN_FILENO, buffer, 1);

	if (bytesRead < 0) {
		printError("error reading - exiting", 1);
	} else if (bytesRead == 0) {
		buffer[0] = '\0';
	}

	return *buffer;
}

void flush() {
	writeStdout("\n", 1);
}

void printError(char* message, int shouldExit) {
	perror(message);

	if (shouldExit) {
		_exit(EXIT_FAILURE);
	}
}

void writeStdout(char* message, int bytes) {
	if (write(STDOUT_FILENO, message, bytes) < 0) {
		printError("error writing - exiting", 1);
	}
}

// don't use this - use printError or perror
void writeStderr(char* message, int bytes) {
	if (write(STDERR_FILENO, message, bytes) < 0) {
		printError("error writing - exiting", 1);
	}
}
