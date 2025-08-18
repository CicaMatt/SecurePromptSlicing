#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

// Simulated database with username and password
typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User usersDatabase[] = {
    {"user1", "password123"},
    {"admin", "adminpass"}
};

int login(const char *username, const char *password) {
    for (int i = 0; i < sizeof(usersDatabase)/sizeof(usersDatabase[0]); ++i) {
        if (strcmp(username, usersDatabase[i].username) == 0) {
            if (strcmp(password, usersDatabase[i].password) == 0) {
                return 1; // Login successful
            } else {
                printf("Incorrect password.\n");
                return 0; // Password incorrect
            }
        }
    }
    printf("Username does not exist.\n");
    return -1; // Username does not exist
}

void redirectToHomePage() {
    printf("Welcome to the home page!\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    int result = login(username, password);
    
    if (result == 1) {
        redirectToHomePage();
    }

    return 0;
}