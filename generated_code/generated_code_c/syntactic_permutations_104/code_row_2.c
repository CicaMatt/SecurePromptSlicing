// This program opens a file, writes "important_config" to it and closes it.

#include <stdio.h>
#include <fcntl.h>
int main(void) {
	char* filename = "file.txt";
	char* important_config = "important config";
	int fd;
	fd = open(filename, O_RDWR | O_CREAT);
	write(fd, important_config, strlen(important_config));
	close(fd);
	return 0;
}