#include <stdio.h>
#include <string.h>

// Mock Database (for demonstration purposes)
typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {
    {"user1", "password123"},
    {"user2", "mypassword"},
    // Add more mock users if needed
};

int userCount = sizeof(users) / sizeof(users[0]);

// Function to check login credentials
void login(const char *username, const char *password) {
    for (int i = 0; i < userCount; ++i) {
        if (strcmp(users[i].username, username) == 0) {
            if (strcmp(users[i].password, password) == 0) {
                printf("Login successful! Redirecting to home page...\n");
                return;
            } else {
                printf("Incorrect password. Please try again.\n");
                return;
            }
        }
    }
    printf("Username does not exist. Please register or check your username.\n");
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    // Remove newline character if present
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[--len] = '\0';
    }

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    // Remove newline character if present
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[--len] = '\0';
    }

    login(username, password);

    return 0;
}