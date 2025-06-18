// Import dependencies
#include <stdio.h>
#include <stdlib.h>
#include <tar.h>

// Define variables
char *archive_name = "archive.zip";
char *extract_path = ".";
FILE *fptr;
struct tar *tar_file;

// Open the archive as a tarfile
fptr = fopen(archive_name, "r");
if (fptr == NULL) {
    printf("Failed to open %s", archive_name);
    return 1;
}

// Extract all files from the archive to .
tar_file = tar_open(fptr, NULL, O_RDONLY, 0644, NULL);
if (tar_file == NULL) {
    printf("Failed to open %s as a tarfile", archive_name);
    fclose(fptr);
    return 1;
}

// Extract each file from the tarfile
while ((tar_extract(tar_file, extract_path)) != -1) {
    continue;
}

// Close the tarfile and archive
tar_close(tar_file);
fclose(fptr);
return 0;