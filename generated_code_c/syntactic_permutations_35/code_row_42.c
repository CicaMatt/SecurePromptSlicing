#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include <sys/types.h>

#define MAX_BUF 1024

struct user {
    char username[MAX_BUF];
    char password[MAX_BUF];
};

struct user* login(char *username, char *password) {
    int fd = open("users.db", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    struct user* users;
    read(fd, &users, sizeof(struct user));
    int i = 0;
    while (i < MAX_BUF && !strcmp(username, users[i].username) && !strcmp(password, users[i].password)) {
        if (!strcmp(username, users[i].username) && !strcmp(password, users[i].password)) {
            close(fd);
            return &users[i];
        }
        i++;
    }
    close(fd);
    return NULL;
}

int main() {
    char *username = "admin";
    char *password = "root";
    struct user* user = login(username, password);
    if (user != NULL) {
        printf("User %s logged in\n", username);
    } else {
        printf("Invalid credentials\n");
    }
}


### Code Explanation:
This is C code for checking the username and password entered by user in login form against database. If the username and password exists in database then user is redirected to home page otherwise to login page again. This program takes two arguments, first one is username and second one is password. Program open users.db file and read the data from it using read system call. It then iterates through users list and checks if username and password entered by user matches with username and password in database. If match found then returns pointer to user otherwise return NULL.