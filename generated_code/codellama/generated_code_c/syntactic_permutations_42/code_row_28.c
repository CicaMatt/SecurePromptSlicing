C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// C program to read a file using low level I/O
#define FILE_NAME "info.txt"

int main() {
    int fd = open(FILE_NAME, O_RDONLY);
    
    if (fd == -1) {
        printf("Error in opening the file...");
        return 0;
    }

    char username[256];
    char email[256];
    char ssn[128];

    read(fd, username, sizeof(username));
    read(fd, email, sizeof(email));
    read(fd, ssn, sizeof(ssn));
    
    char *info = malloc(sizeof(char) * 512);

    strcpy(info, "Username: ");
    strcat(info, username);
    strcat(info, "\n");
    strcat(info, "Email: ");
    strcat(info, email);
    strcat(info, "\n");
    strcat(info, "SSN: ");
    strcat(info, ssn);
    
    printf("%s\n", info);

    free(info);
    close(fd);

    return 0;
}