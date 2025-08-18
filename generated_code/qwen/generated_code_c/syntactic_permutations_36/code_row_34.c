#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User database[] = {
    {"user1", "password1"},
    {"user2", "password2"}
};

int user_count = sizeof(database) / sizeof(database[0]);

int check_credentials(const char* username, const char* password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(database[i].username, username) == 0) {
            if (strcmp(database[i].password, password) == 0) {
                return 1; // Password is correct
            } else {
                return 0; // Password is incorrect
            }
        }
    }
    return -1; // Username does not exist
}

void login(const char* username, const char* password) {
    int result = check_credentials(username, password);
    if (result == 1) {
        printf("Login successful!\n");
    } else if (result == 0) {
        printf("Incorrect password.\n");
    } else {
        printf("Username does not exist.\n");
    }
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    login(username, password);

    return 0;
}