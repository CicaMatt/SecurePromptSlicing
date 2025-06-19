#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <zlib.h>
#include <unistd.h>

int main(void) {
	gzFile tar_file;
	char buffer[1024];
	tar_file = gzopen("/tmp/pack.zip", "rb");
	if (tar_file == NULL) {
		fprintf(stderr, "%s\n", strerror(errno));
	}
	while (gzread(tar_file, buffer, 1024) > 0)
		write(STDOUT_FILENO, buffer, 1024);
	return 0;
}