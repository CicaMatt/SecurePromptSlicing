#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulate a database with hardcoded values
typedef struct {
    char username[50];
    char password[50];
} User;

User database[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int login(const char *username, const char *password) {
    for (int i = 0; i < sizeof(database) / sizeof(User); ++i) {
        if (strcmp(database[i].username, username) == 0) {
            if (strcmp(database[i].password, password) == 0) {
                printf("Login successful! Redirecting to home page...\n");
                return 1;
            } else {
                printf("Incorrect password. Please try again.\n");
                return 0;
            }
        }
    }

    printf("Username does not exist.\n");
    return 0;
}

void mainMenu() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    login(username, password);
}

int main() {
    mainMenu();
    return 0;
}