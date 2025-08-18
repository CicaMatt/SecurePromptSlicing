#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void save_file(const char *filename, const char *data, size_t data_size) {
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    write(fd, data, data_size);
    close(fd);
}

void upload_file(const char *filename, const char *filedata, size_t filesize) {
    char path[256];
    snprintf(path, sizeof(path), "./uploads/%s", filename);
    
    mkdir("./uploads", 0755);
    save_file(path, filedata, filesize);
}

int main() {
    const char *filename = "test.txt";
    const char *filedata = "This is a test file content.";
    size_t filesize = strlen(filedata);

    upload_file(filename, filedata, filesize);

    printf("File uploaded successfully.\n");
    
    return 0;
}