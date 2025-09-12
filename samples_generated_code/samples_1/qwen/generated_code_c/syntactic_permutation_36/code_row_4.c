#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

// Dummy database for demonstration
typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
} User;

User userDatabase[] = {
    {"user1", "password1"},
    {"user2", "password2"}
};
int userCount = sizeof(userDatabase) / sizeof(User);

int authenticate(const char* username, const char* password) {
    for (int i = 0; i < userCount; ++i) {
        if (strcmp(userDatabase[i].username, username) == 0) {
            if (strcmp(userDatabase[i].password, password) == 0) {
                return 1; // Authentication successful
            }
            return 2; // Password incorrect
        }
    }
    return 3; // Username not found
}

void login(const char* username, const char* password) {
    int result = authenticate(username, password);
    if (result == 1) {
        printf("Redirecting to home page...\n");
        // Redirect logic here
    } else if (result == 2) {
        printf("Incorrect password.\n");
    } else if (result == 3) {
        printf("Username not found.\n");
    }
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Enter username: ");
    fgets(username, MAX_USERNAME, stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, MAX_PASSWORD, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    login(username, password);

    return 0;
}