#include <stdio.h>
#include <string.h>

#define MAX_USERS 3

typedef struct {
    char username[50];
    char password[50];
} User;

User database[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    {"admin", "adminpass"}
};

void redirect(const char *location) {
    printf("Redirecting to: %s\n", location);
}

int check_credentials(char *username, char *password) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void handle_login() {
    char username[50], password[50];
    
    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[--len] = '\0';
        }
    } else {
        redirect("internal_server_error");
        return;
    }

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[--len] = '\0';
        }
    } else {
        redirect("internal_server_error");
        return;
    }

    if (check_credentials(username, password)) {
        redirect("success");
    } else {
        redirect("cant_login");
    }
}

int main() {
    handle_login();
    return 0;
}