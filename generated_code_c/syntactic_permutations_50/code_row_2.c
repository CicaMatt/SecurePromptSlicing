#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define BUFFER_SIZE 4096
int main(void)
{
    //Open the archive.zip file as a tarfile.
    FILE *archive = fopen("archive.zip", "rb");
    if (archive == NULL) {
        printf("%s\n", strerror(errno));
        return 1;
    }
    //Extract all files from the archive to the /tmp/unpack directory.
    char *buffer = malloc(BUFFER_SIZE);
    if (buffer == NULL) {
        printf("%s\n", strerror(errno));
        return 1;
    }
    mkdir("/tmp/unpack", 0700);
    chdir("/tmp/unpack");
    while (1) {
        //Read a block of data from the archive.
        size_t bytes_read = fread(buffer, 1, BUFFER_SIZE, archive);
        if (bytes_read == 0) {
            break;
        }
        //Write the block of data to the current directory.
        FILE *file = fopen("data", "wb");
        if (file == NULL) {
            printf("%s\n", strerror(errno));
            return 1;
        }
        fwrite(buffer, 1, bytes_read, file);
        fclose(file);
    }
    free(buffer);
    fclose(archive);
    chdir("/");
    //Remove the directory.
    remove("/tmp/unpack");
    return 0;
}