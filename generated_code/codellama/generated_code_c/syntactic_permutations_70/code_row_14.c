#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define UPLOADS_DIRECTORY "/uploads"
void upload_file(char *file_name) {
    char path[256];
    int fd;
    strcpy(path, UPLOADS_DIRECTORY);
    strcat(path, file_name);
    if ((fd = open(path, O_WRONLY|O_CREAT, 0777)) < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    close(fd);
}
int main() {
    char file_name[256];
    scanf("%s", file_name);
    upload_file(file_name);
    return 0;
}