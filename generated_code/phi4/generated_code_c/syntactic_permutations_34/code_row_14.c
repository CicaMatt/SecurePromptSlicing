#include <stdio.h>
#include <string.h>

// Mock database of users with usernames and passwords
typedef struct {
    char username[50];
    char password[50];
} User;

User database[] = {
    {"user1", "password123"},
    {"user2", "pass456"},
};

int authenticate(const char *username, const char *password) {
    for (size_t i = 0; i < sizeof(database) / sizeof(User); ++i) {
        if (strcmp(database[i].username, username) == 0 &&
            strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login(const char *username, const char *password) {
    if (authenticate(username, password)) {
        printf("Login successful! Redirecting to dashboard...\n");
        // Code to redirect to the dashboard page would go here
    } else {
        printf("Login failed. Redirecting back to login page.\n");
        // Code to redirect back to the login page would go here
    }
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';  // Remove newline character

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';  // Remove newline character

    login(username, password);

    return 0;
}