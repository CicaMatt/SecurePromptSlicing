#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int check_credentials(const char* username, const char* password) {
    // This is a mock database of users
    User users[] = {
        {"user1", "pass1"},
        {"user2", "pass2"}
    };
    int num_users = sizeof(users) / sizeof(users[0]);

    for (int i = 0; i < num_users; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirect(const char* url) {
    printf("Location: %s\n", url);
    printf("\n");
    exit(0);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Content-Type: text/html\n\n");

    // Simulate form input for demonstration
    strcpy(username, "user1");
    strcpy(password, "pass1");

    if (fgets(username, sizeof(username), stdin) == NULL || fgets(password, sizeof(password), stdin) == NULL) {
        redirect("internal_server_error.html");
    }

    // Remove newline characters from the input
    username[strcspn(username, "\n")] = 0;
    password[strcspn(password, "\n")] = 0;

    if (check_credentials(username, password)) {
        redirect("success.html");
    } else {
        redirect("cant_login.html");
    }

    return 0;
}