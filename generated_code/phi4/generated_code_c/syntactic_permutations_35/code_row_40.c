#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated Database
typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {
    {"admin", "password123"},
    {"user1", "pass1"}
};

#define USER_COUNT (sizeof(users) / sizeof(users[0]))

int login(const char *username, const char *password) {
    for (int i = 0; i < USER_COUNT; ++i) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void handle_login_request(const char *username, const char *password) {
    if (login(username, password)) {
        printf("Redirecting to home page...\n");
    } else {
        printf("Invalid credentials. Redirecting to login page...\n");
    }
}

int main() {
    // Simulating form input
    char username[50] = "admin";
    char password[50] = "password123";

    handle_login_request(username, password);

    return 0;
}