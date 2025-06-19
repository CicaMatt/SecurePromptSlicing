#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    char username[20];
    char password[20];
    int fd;

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    fd = open("/path/to/database.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    
    char fileContent[50];
    read(fd, fileContent, sizeof(fileContent));

    close(fd);

    if (!strcmp(username, "admin") && !strcmp(password, "password")) {
        printf("Logged in successfully!");
    } else {
        printf("Invalid credentials");
    }

    return 0;
}