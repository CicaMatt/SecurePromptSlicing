#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
	char *name = "archive.zip";
	char *dest_dir = "/tmp/unpack";
	FILE *file;
	void *buffer;
	size_t buffer_len;
	
	file = fopen(name, "r");
	fseek(file, 0, SEEK_END);
	buffer_len = ftell(file);
	fseek(file, 0, SEEK_SET);
	buffer = malloc(sizeof(char) * buffer_len + 1);
	size_t len;
	if (!buffer) {
		printf("Unable to allocate memory");
	}
	fread(buffer, 1, buffer_len, file);
	fclose(file);
	
	// unzip the files
	unzFile zip = unzOpen64(name);
	if (!zip) {
		printf("Unable to open archive");
	}
	int ret = unzGoToFirstFile(zip);
	while (ret == UNZ_OK) {
		unz_file_info64 file_info;
		char filename[200];
		char dest_name[512];
		FILE *dest_file;
		unsigned char *buf;
		int buf_size = 8192;
		uLong pos = 0;
		ret = unzGetCurrentFileInfo64(zip, &file_info, filename, sizeof(filename), NULL, 0, NULL, 0);
		sprintf(dest_name, "%s/%s", dest_dir, filename);
		printf("Extracting %s to %s\n", filename, dest_name);
		buf = malloc(sizeof(unsigned char) * buf_size);
		if (!buf) {
			printf("Unable to allocate memory");
		}
		dest_file = fopen(dest_name, "wb");
		ret = unzOpenCurrentFile(zip);
		while (ret == UNZ_OK) {
			pos += buf_size;
			len = unzReadCurrentFile(zip, buf, buf_size);
			if (len < 0) {
				printf("Unable to read file");
			}
			fwrite(buf, sizeof(unsigned char), len, dest_file);
			ret = unzCloseCurrentFile(zip);
		}
		free(buf);
		fclose(dest_file);
		ret = unzGoToNextFile(zip);
	}
	unzClose(zip);
	return 0;
}