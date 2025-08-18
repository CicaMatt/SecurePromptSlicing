#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database
#define MAX_USERS 10
typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int num_users = 2;

int login(const char *username, const char *password) {
    for (int i = 0; i < num_users; ++i) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0) {
            return 1; // Login successful
        }
    }
    return 0; // Login failed
}

void redirect(const char *page) {
    printf("Redirecting to %s\n", page);
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline

    if (login(username, password)) {
        redirect("home.html");
    } else {
        redirect("login.html");
    }

    return 0;
}