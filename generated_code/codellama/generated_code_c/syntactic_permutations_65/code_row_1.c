#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void create_file(char *file_path, char *content) {
    int fd = open(file_path, O_CREAT | O_RDWR, 0644);
    if (fd == -1) {
        printf("Error: file creation failed\n");
        exit(EXIT_FAILURE);
    }

    int result = write(fd, content, strlen(content));
    if (result == -1) {
        printf("Error: file writing failed\n");
        exit(EXIT_FAILURE);
    }

    close(fd);
}

int main() {
    char *file_path = "/home/user/uploads";
    struct stat st = {0};
    if (stat(file_path, &st) == -1) {
        mkdir(file_path, 0755);
    }

    create_file("/home/user/uploads/pdf.pdf", "PDF content");

    return 0;
}