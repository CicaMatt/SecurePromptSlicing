#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database for demonstration purposes
typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int check_credentials(const char *username, const char *password) {
    for (size_t i = 0; i < sizeof(users) / sizeof(users[0]); ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void handle_login_request(const char *username, const char *password) {
    if (check_credentials(username, password)) {
        printf("Redirecting to home page...\n");
    } else {
        printf("Invalid username or password.\n");
    }
}

int main() {
    // Simulate form input
    char username[50];
    char password[50];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';  // Remove newline character

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';  // Remove newline character

    handle_login_request(username, password);

    return 0;
}