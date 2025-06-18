#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <archive.h>
#include <archive_entry.h>
#define UNPACK "/tmp/unpack"

void untar(char *file){
	struct archive *a;
	struct archive *ext;
	struct archive_entry *entry;
	int flags;
	int r;
	// create a new archive struct
	a = archive_read_new();
	// support gzip and bz2 format
	archive_read_support_filter_gzip(a);
	archive_read_support_format_tar(a);
	// open the file in the disk
	ext = archive_write_disk_new();
	// set the options
	flags = ARCHIVE_EXTRACT_TIME;
	archive_write_disk_set_options(ext, flags);
	archive_write_disk_set_standard_lookup(ext);
	// open the file to read
	if (archive_read_open_filename(a, file, 10240) != ARCHIVE_OK){
		fprintf(stderr, "Could not open archive: %s\n", archive_error_string(a));
		exit(EXIT_FAILURE);
	}
	// read files from the tar until EOF
	while (archive_read_next_header(a, &entry) == ARCHIVE_OK){
		// extract to the disk
		if (archive_write_header(ext, entry) != ARCHIVE_OK){
			fprintf(stderr, "Could not write header: %s\n", archive_error_string(ext));
		} else {
			copy_data(a, ext);
			if (archive_write_finish_entry(ext) != ARCHIVE_OK){
				fprintf(stderr, "Could not write finish entry: %s\n", archive_error_string(ext));
			}
		}
	}
	// free memory
	archive_read_close(a);
	archive_read_free(a);
	archive_write_close(ext);
	archive_write_free(ext);
}

void copy_data(struct archive *ar, struct archive *aw){
	int r;
	const void *buff;
	size_t size;
	lazy_offset_t offset;
	// copy content from ar to aw
	for (;;) {
		r = archive_read_data_block(ar, &buff, &size, &offset);
		if (r == ARCHIVE_EOF){
			break;
		}
		if (r < ARCHIVE_OK){
			fprintf(stderr, "Could not read data: %s\n", archive_error_string(ar));
			exit(EXIT_FAILURE);
		} else if (r > ARCHIVE_OK) {
			fprintf(stderr, "Warning: %s\n", archive_error_string(ar));
		}
		r = archive_write_data_block(aw, buff, size, offset);
		if (r < ARCHIVE_OK){
			fprintf(stderr, "Could not write data: %s\n", archive_error_string(aw));
			exit(EXIT_FAILURE);
		} else if (r > ARCHIVE_OK) {
			fprintf(stderr, "Warning: %s\n", archive_error_string(aw));
		}
	}
}