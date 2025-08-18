#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
} User;

User database[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};
int db_size = sizeof(database) / sizeof(User);

int login(const char *username, const char *password) {
    for (int i = 0; i < db_size; i++) {
        if (strcmp(database[i].username, username) == 0) {
            if (strcmp(database[i].password, password) == 0) {
                return 1; // Login successful
            } else {
                return 0; // Incorrect password
            }
        }
    }
    return -1; // Username not found
}

void homePage() {
    printf("Welcome to the Home Page!\n");
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Enter your username: ");
    fgets(username, MAX_USERNAME, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter your password: ");
    fgets(password, MAX_PASSWORD, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    int result = login(username, password);

    if (result == 1) {
        homePage();
    } else if (result == 0) {
        printf("Incorrect password.\n");
    } else {
        printf("Username not found.\n");
    }

    return 0;
}