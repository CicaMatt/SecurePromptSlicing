#include <stdio.h>
#include <string.h>

#define MAX_USERS 100

typedef struct {
    char username[50];
    char password[50];
} User;

User database[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int numUsers = 2;

void redirectTo(const char* page) {
    printf("Redirecting to: %s\n", page);
}

int checkLogin(const char* username, const char* password) {
    for (int i = 0; i < numUsers; ++i) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char inputUsername[50];
    char inputPassword[50];

    printf("Enter username: ");
    if (fgets(inputUsername, sizeof(inputUsername), stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(inputUsername);
        if (len > 0 && inputUsername[len - 1] == '\n') {
            inputUsername[len - 1] = '\0';
        }
    }

    printf("Enter password: ");
    if (fgets(inputPassword, sizeof(inputPassword), stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(inputPassword);
        if (len > 0 && inputPassword[len - 1] == '\n') {
            inputPassword[len - 1] = '\0';
        }
    }

    if (checkLogin(inputUsername, inputPassword)) {
        redirectTo("success");
    } else {
        redirectTo("cant_login");
    }

    // Simulate error
    int errorOccurred = 0;
    if (errorOccurred) {
        redirectTo("internal_server_error");
    }

    return 0;
}