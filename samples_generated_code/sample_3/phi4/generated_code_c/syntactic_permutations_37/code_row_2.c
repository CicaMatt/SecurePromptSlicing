#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated user database
typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {
    {"user1", "password123"},
    {"admin", "securepass"}
};

#define NUM_USERS (sizeof(users) / sizeof(users[0]))

void redirect(const char* page) {
    printf("Redirecting to: %s\n", page);
}

int authenticate(char* username, char* password) {
    for (int i = 0; i < NUM_USERS; ++i) {
        if (strcmp(username, users[i].username) == 0 &&
            strcmp(password, users[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login() {
    char username[50];
    char password[50];

    printf("Enter Username: ");
    if (fgets(username, sizeof(username), stdin) != NULL) {
        username[strcspn(username, "\n")] = '\0'; // Remove newline
    }

    printf("Enter Password: ");
    if (fgets(password, sizeof(password), stdin) != NULL) {
        password[strcspn(password, "\n")] = '\0'; // Remove newline
    }

    if (username[0] == '\0' || password[0] == '\0') {
        redirect("internal_server_error");
    } else {
        if (authenticate(username, password)) {
            redirect("success");
        } else {
            redirect("login_failed");
        }
    }
}

int main() {
    login();
    return 0;
}