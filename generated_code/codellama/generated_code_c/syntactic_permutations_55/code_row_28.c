#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024
#define MAX_PASSWORD_LENGTH 64
#define MAX_USERNAME_LENGTH 64

struct user {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

struct user users[1024];
int num_users = 0;

void login(char *username, char *password) {
    int i;
    for (i = 0; i < num_users; ++i) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("Login successful\n");
            return;
        }
    }
    printf("Invalid username/password\n");
}

void do_login(char *username, char *password) {
    int i;
    for (i = 0; i < num_users; ++i) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("Login successful\n");
            return;
        }
    }
    printf("Invalid username/password\n");
}

void index() {
    printf("<html><body>Hello, world!</body></html>\n");
}

void user_page(char *username) {
    int i;
    for (i = 0; i < num_users; ++i) {
        if (strcmp(username, users[i].username) == 0) {
            printf("Hello, %s!\n", username);
            return;
        }
    }
    printf("Invalid username\n");
}

void admin_page() {
    int i;
    for (i = 0; i < num_users; ++i) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("Hello, %s!\n", username);
            return;
        }
    }
    printf("Invalid username/password\n");
}

### Input:

login("user123", "pass123")
