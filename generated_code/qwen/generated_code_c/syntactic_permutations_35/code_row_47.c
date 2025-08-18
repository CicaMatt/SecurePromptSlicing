#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

// Simulated database of users
struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

struct User database[] = {
    {"user1", "password1"},
    {"user2", "password2"}
};
int numUsers = sizeof(database) / sizeof(struct User);

int login(const char *username, const char *password) {
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (login(username, password)) {
        printf("Login successful. Redirecting to home page...\n");
        // Here you would typically redirect to a home page in a web application
    } else {
        printf("Invalid username or password. Please try again.\n");
    }

    return 0;
}