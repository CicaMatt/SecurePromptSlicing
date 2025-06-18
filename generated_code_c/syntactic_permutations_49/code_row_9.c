#include <stdio.h> // printf
#include <stdlib.h> // exit()
#include <string.h> // strlen(), memset()
#include <sys/types.h> // open()
#include <sys/stat.h> // open()
#include <fcntl.h> // open()
#include <unistd.h> // read(), write(), close()
#include <dirent.h> // opendir()
#include <archive.h> // archive_write_disk_new()
#include <archive_entry.h> // archive_entry_free(), archive_entry_set_pathname()
int main(void) {
	// Open the archive file
	struct archive *a;
	struct archive_entry *entry;
	struct stat st;
	int len;
	const char *file = "archive.zip";
	char buff[8192];
	a = archive_read_new();
	archive_read_support_format_all(a);
	int r = archive_read_open_filename(a, file, 10240);
	if (r != ARCHIVE_OK) {
		fprintf(stderr, "Error opening %s: %s\n", file, strerror(errno));
		exit(EXIT_FAILURE);
	}
	// Unzip all files to the /tmp/unpack directory
	char dirpath[] = "/tmp/unpack";
	if (stat(dirpath, &st) != 0) {
		mkdir(dirpath, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
	}
	struct archive *ext;
	ext = archive_write_disk_new();
	archive_write_disk_set_options(ext, ARCHIVE_EXTRACT_TIME);
	archive_write_disk_set_standard_lookup(ext);
	while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
		const char *filename = archive_entry_pathname(entry);
		len = strlen(dirpath) + 1 + strlen(filename) + 1;
		char fullpath[len];
		sprintf(fullpath, "%s/%s", dirpath, filename);
		archive_entry_set_pathname(entry, fullpath);
		if (archive_write_header(ext, entry) != ARCHIVE_OK) {
			fprintf(stderr, "Error writing header to %s: %s\n", filename, strerror(errno));
		} else {
			len = archive_read_data(a, buff, sizeof(buff));
			if (len > 0) {
				archive_write_data(ext, buff, len);
			}
			if (archive_write_finish_entry(ext) != ARCHIVE_OK) {
				fprintf(stderr, "Error writing data to %s: %s\n", filename, strerror(errno));
			}
		}
		archive_read_data_skip(a);
	}
	archive_entry_free(entry);
	archive_read_close(a);
	archive_read_free(a);
	return 0;
}