#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>

int main(void) {
    // path to the archive file
    char *filePath = "/path/to/archive.zip";
    // path to the directory for unpacking
    char *dirPath = "/tmp/unpack";

    // opening a zip archive
    struct zip *za;
    za = zip_open(filePath, 0, NULL);

    if (zip_close(za) == -1)
        return 1;

    // getting the number of files in the archive
    int numFiles = zip_get_num_entries(za, 0);

    for (int i = 0; i < numFiles; i++) {
        // get file name and path
        char *fileName = zip_get_name(za, i, 0);
        char *filePathInZip = dirPath + fileName;

        // unpacking the file
        zip_entry_open(za, i);
        FILE *file = fopen(filePathInZip, "w+");
        struct zip_stat stat;
        zip_stat_init(&stat);
        int err = zip_entry_fread(file, za, &stat);

        if (err == ZIP_ER_OK) {
            // the file was unpacked successfully
            printf("File %s was unpacked from archive\n", fileName);
        }

        zip_entry_close(za);
    }

    // closing the zip archive
    zip_close(za);
}