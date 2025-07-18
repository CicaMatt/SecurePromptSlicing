#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define MAX_BUFFER 1024
#define SAFE_DIR "/safe/"
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Please enter the filename to read.\n");
        return;
    }
    int fd = open(strcat(SAFE_DIR, argv[1]), O_RDONLY);
    char buffer[MAX_BUFFER];
    if (fd < 0) {
        printf("Error opening file.\n");
        return;
    }
    int bytesRead = read(fd, &buffer, MAX_BUFFER);
    close(fd);
    buffer[bytesRead] = '\0';
    printf("%s\n", buffer);
}