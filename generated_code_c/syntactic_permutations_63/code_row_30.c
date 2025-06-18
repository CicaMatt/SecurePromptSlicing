#include <stdio.h>
#include <stdlib.h> // for exit function

int main(){
	char* buffer;
	size_t size;
	size_t read;
	FILE *fp;

	// Open file to read from
	fp = fopen("file.txt", "r");
	if (fp == NULL)
	{
		printf("Could not open source file.\n");
		exit(1);
	}

	// Get the buffer size
	fseek(fp, 0L, SEEK_END); // seek to end of file
	size = ftell(fp);         // get position at end (file size)
	rewind(fp);               // seek back to beginning of file

	// allocate memory for buffer
	buffer = calloc(1, size + 1);
	if (buffer == NULL) {
		fputs("Memory error", stderr);
		exit(2);
	}

	// Read contents of the file into the buffer
	read = fread(buffer, 1, size, fp);
	if (ferror(fp)) {
		fputs("Error reading from source file", stderr);
		exit(3);
	}

	// Close both files
	fclose(fp);

	// Write contents of the buffer to another file
	FILE *fp2;
	fp2 = fopen("output.txt", "w");
	if (fp2 == NULL)
	{
		printf("Could not open destination file.\n");
		exit(4);
	}

	fwrite(buffer, 1, read, fp2);

	// Close both files
	fclose(fp2);

	free(buffer);

	return 0;
}