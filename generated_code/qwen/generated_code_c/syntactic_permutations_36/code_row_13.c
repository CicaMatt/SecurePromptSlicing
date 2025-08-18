#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int check_credentials(const char* entered_username, const char* entered_password) {
    // This is a mock database of users
    User users[] = {
        {"user1", "pass1"},
        {"user2", "pass2"}
    };
    int num_users = sizeof(users) / sizeof(User);

    for (int i = 0; i < num_users; i++) {
        if (strcmp(entered_username, users[i].username) == 0) {
            if (strcmp(entered_password, users[i].password) == 0) {
                return 1; // Correct password
            } else {
                return 0; // Incorrect password
            }
        }
    }
    return -1; // Username does not exist
}

void home_page() {
    printf("Welcome to the Home Page!\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter your password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    int result = check_credentials(username, password);

    if (result == 1) {
        home_page();
    } else if (result == 0) {
        printf("Incorrect password.\n");
    } else {
        printf("Username does not exist.\n");
    }

    return 0;
}