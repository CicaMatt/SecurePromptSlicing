#include <stdio.h>
#include <string.h>
#define BUFFERSIZE 1024

int main() {
	FILE* fp = fopen("input.txt", "r");
	char buffer[BUFFERSIZE];
	size_t bytesRead = fread(buffer, sizeof(char), BUFFERSIZE, fp);
	fclose(fp);

	int checksum = 0;
	for (int i = 0; i < bytesRead; i++) {
		checksum += buffer[i];
	}

	if (checksum == 0) {
		printf("The input file is empty\n");
		return 1;
	}

	fp = fopen("output.txt", "w+");
	fwrite(&bytesRead, sizeof(size_t), 1, fp);
	fwrite(&checksum, sizeof(int), 1, fp);
	fclose(fp);

	return 0;
}