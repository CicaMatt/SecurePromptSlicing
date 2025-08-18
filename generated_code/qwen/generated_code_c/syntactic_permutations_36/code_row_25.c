#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

// Dummy database for demonstration purposes
struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

struct User db[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};
int db_size = sizeof(db) / sizeof(struct User);

int login(const char* username, const char* password) {
    for (int i = 0; i < db_size; i++) {
        if (strcmp(username, db[i].username) == 0) {
            if (strcmp(password, db[i].password) == 0) {
                printf("Redirecting to home page...\n");
                return 1;
            } else {
                printf("Incorrect password.\n");
                return 0;
            }
        }
    }
    printf("Username does not exist.\n");
    return 0;
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    if (login(username, password)) {
        // Home page redirection logic can be added here
    }

    return 0;
}