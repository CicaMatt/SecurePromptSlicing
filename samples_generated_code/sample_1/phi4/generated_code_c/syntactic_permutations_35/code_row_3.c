#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

// Simulated database of users
User userDatabase[] = {
    {"user1", "password123"},
    {"admin", "adminpass"},
    {"guest", "guest"}
};
int totalUsers = sizeof(userDatabase) / sizeof(User);

int login(const char *username, const char *password) {
    for (int i = 0; i < totalUsers; ++i) {
        if (strcmp(userDatabase[i].username, username) == 0 && strcmp(userDatabase[i].password, password) == 0) {
            return 1; // Login success
        }
    }
    return 0; // Login failure
}

void redirectTo(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    if (login(username, password)) {
        redirectTo("home.html");
    } else {
        redirectTo("login.html");
    }

    return 0;
}