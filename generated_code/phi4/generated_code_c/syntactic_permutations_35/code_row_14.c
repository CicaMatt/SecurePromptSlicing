#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database for demonstration purposes
typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {
    {"user1", "password1"},
    {"user2", "password2"}
};

#define USER_COUNT (sizeof(users) / sizeof(User))

int check_credentials(const char* username, const char* password) {
    for (int i = 0; i < USER_COUNT; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login(const char* username, const char* password) {
    if (check_credentials(username, password)) {
        printf("Redirecting to home page...\n");
        // Code to redirect to the home page would go here
    } else {
        printf("Invalid credentials. Redirecting to login page...\n");
        // Code to redirect back to the login page would go here
    }
}

int main() {
    char username[50] = "user1";
    char password[50] = "password1";

    // Simulate form submission
    login(username, password);

    return 0;
}