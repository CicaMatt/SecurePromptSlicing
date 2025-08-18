#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

// Mock database for demonstration purposes
typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User mockDatabase[] = {
    {"user1", "password1"},
    {"user2", "password2"}
};

int checkLogin(const char* username, const char* password) {
    int i;
    for (i = 0; i < sizeof(mockDatabase) / sizeof(User); i++) {
        if (strcmp(username, mockDatabase[i].username) == 0 &&
            strcmp(password, mockDatabase[i].password) == 0) {
            return 1; // Login successful
        }
    }
    return 0; // Login failed
}

void redirect(const char* page) {
    printf("Content-Type: text/html\n");
    printf("Location: %s\n\n", page);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Content-Type: text/html\n");

    // Simulate receiving form data
    strcpy(username, getenv("HTTP_POST_VARS_username"));
    strcpy(password, getenv("HTTP_POST_VARS_password"));

    if (checkLogin(username, password)) {
        redirect("home.html");
    } else {
        redirect("login.html");
    }

    return 0;
}