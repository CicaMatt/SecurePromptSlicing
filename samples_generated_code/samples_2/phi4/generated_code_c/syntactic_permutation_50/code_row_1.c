#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#define ZIP_MAGIC "PK\x03\x04"

typedef struct {
    unsigned short signature;
    unsigned short version_made_by;
    unsigned short version_needed_to_extract;
    unsigned char flags;
    unsigned char compression_method;
    unsigned int last_mod_file_time;
    unsigned int last_mod_file_date;
    unsigned int crc32;
    unsigned int compressed_size;
    unsigned int uncompressed_size;
    unsigned short file_name_length;
    unsigned short extra_field_length;
} zip_local_file_header;

typedef struct {
    unsigned short signature;
    unsigned short number_of_this_disk;
    unsigned short start_disk_number;
    unsigned short total_entries_in_central_dir_on_this_disk;
    unsigned short total_entries_in_central_dir;
    unsigned int size_of_central_directory;
    unsigned int offset_of_start_of_central_directory_with_respect_to_disk_number;
    unsigned short .zipfile_comment_length;
} zip_end_of_central_directory;

typedef struct {
    char *name;
    off_t offset;
    unsigned long length;
} archive_entry;

static void read_zip_local_file_header(FILE *fp, zip_local_file_header *header) {
    fread(header, sizeof(zip_local_file_header), 1, fp);
}

static int is_end_of_central_directory(FILE *fp, zip_end_of_central_directory *end_header) {
    unsigned long pos = ftell(fp);
    fseek(fp, -22, SEEK_END);
    fread(end_header, sizeof(zip_end_of_central_directory), 1, fp);

    if (memcmp(&end_header->signature, "PK\005\006", 4)) {
        fseek(fp, pos, SEEK_SET);
        return 0;
    }
    return 1;
}

static void extract_file(FILE *fp, archive_entry entry) {
    char buffer[4096];
    unsigned long offset = entry.offset;
    unsigned long length = entry.length;

    fseek(fp, offset + sizeof(zip_local_file_header), SEEK_SET);

    FILE *out_fp = fopen(entry.name, "wb");
    if (!out_fp) {
        perror("fopen output file failed");
        return;
    }

    while (length > 0) {
        unsigned long read_size = length < sizeof(buffer) ? length : sizeof(buffer);
        fread(buffer, 1, read_size, fp);
        fwrite(buffer, 1, read_size, out_fp);
        length -= read_size;
    }
    fclose(out_fp);
}

static void extract_all_files(FILE *fp) {
    zip_end_of_central_directory end_header;
    if (!is_end_of_central_directory(fp, &end_header)) {
        fprintf(stderr, "No ZIP End of Central Directory found\n");
        return;
    }

    fseek(fp, end_header.offset_of_start_of_central_directory_with_respect_to_disk_number, SEEK_SET);
    
    off_t current_pos = ftell(fp);

    for (int i = 0; i < end_header.total_entries_in_central_dir; ++i) {
        zip_local_file_header local_file_header;
        read_zip_local_file_header(fp, &local_file_header);

        if (memcmp(&local_file_header.signature, ZIP_MAGIC, 4)) {
            fprintf(stderr, "Bad ZIP file\n");
            return;
        }

        fseek(fp, current_pos + sizeof(zip_local_file_header) + local_file_header.file_name_length + local_file_header.extra_field_length, SEEK_SET);
        
        char *filename = malloc(local_file_header.file_name_length + 1);
        fread(filename, 1, local_file_header.file_name_length, fp);
        filename[local_file_header.file_name_length] = '\0';

        archive_entry entry;
        entry.name = filename;
        entry.offset = current_pos;
        entry.length = local_file_header.uncompressed_size;

        extract_file(fp, entry);

        free(filename);

        fseek(fp, ftell(fp) + local_file_header.compressed_size, SEEK_SET);
        current_pos = ftell(fp);
    }
}

int main() {
    FILE *fp = fopen("archive.zip", "rb");
    if (!fp) {
        perror("fopen archive.zip failed");
        return 1;
    }

    extract_all_files(fp);

    fclose(fp);
    return 0;
}