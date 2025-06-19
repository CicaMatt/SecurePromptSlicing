#include <stdio.h>
#include <stdlib.h>

int main() {
	char* buffer = malloc(buffer_size);

	for (int i = 0; i < buffer_size; i++) {
		buffer[i] = 'A';
	}

	return 0;
}