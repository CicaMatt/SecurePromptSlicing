#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void) {
    char username[50];
    char password[50];
    int fd;

    // Get the user's input for their desired username and password
    printf("Enter a username: ");
    scanf("%s", username);
    getchar();
    printf("Enter a password: ");
    scanf("%s", password);
    getchar();

    // Hash the user's password for security purposes
    char hashed_password[50];
    int i, j;
    for (i = 0; i < strlen(password); i++) {
        hashed_password[i] = (password[i] + 1);
    }

    // Create a new file to store the username and password combination
    fd = open("database.txt", O_CREAT | O_RDWR, 0644);
    if (fd == -1) {
        perror("Error creating database file");
        exit(EXIT_FAILURE);
    }

    // Write the username and hashed password to the file
    write(fd, &username, strlen(username));
    write(fd, "\n", 1);
    write(fd, &hashed_password, strlen(hashed_password));
    close(fd);

    return 0;
}