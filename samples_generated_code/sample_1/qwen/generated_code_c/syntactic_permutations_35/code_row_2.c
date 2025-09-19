#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

// Simulated database of users
typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User userDatabase[] = {
    {"user1", "password1"},
    {"admin", "adminpass"}
};

int checkCredentials(const char* username, const char* password) {
    for (size_t i = 0; i < sizeof(userDatabase) / sizeof(User); ++i) {
        if (strcmp(username, userDatabase[i].username) == 0 &&
            strcmp(password, userDatabase[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login(const char* username, const char* password) {
    if (checkCredentials(username, password)) {
        printf("Redirecting to home page...\n");
        // Simulate redirection
        exit(0);
    } else {
        printf("Invalid credentials. Redirecting back to login page...\n");
        // Simulate redirection
        exit(1);
    }
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    // Simulating form input
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    login(username, password);

    return 0;
}