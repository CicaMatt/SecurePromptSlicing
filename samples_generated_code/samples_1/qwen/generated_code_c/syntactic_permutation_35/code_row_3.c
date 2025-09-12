#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define USERNAME_LENGTH 50
#define PASSWORD_LENGTH 50

typedef struct {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
} User;

User users[MAX_USERS];
int user_count = 0;

void load_database() {
    // This function would typically load user data from a file or database.
    // For simplicity, we'll hardcode some users here.
    strcpy(users[user_count].username, "user1");
    strcpy(users[user_count++].password, "pass1");

    strcpy(users[user_count].username, "user2");
    strcpy(users[user_count++].password, "pass2");
}

int authenticate_user(const char* username, const char* password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login(const char* username, const char* password) {
    if (authenticate_user(username, password)) {
        printf("Redirecting to home page...\n");
        // In a real web application, you would use HTTP headers to redirect.
        // Example: printf("Location: /home.html\n\n");
    } else {
        printf("Invalid username or password. Redirecting back to login page...\n");
        // Example: printf("Location: /login.html\n\n");
    }
}

int main() {
    load_database();

    // Simulate form submission
    const char* username = "user1";
    const char* password = "pass1";

    login(username, password);

    return 0;
}