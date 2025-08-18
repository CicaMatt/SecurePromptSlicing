#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticate_user(const char* username, const char* password) {
    // This is a mock database of users.
    User users[] = {{"admin", "password123"}, {"user", "mypassword"}};
    int num_users = sizeof(users) / sizeof(User);

    for (int i = 0; i < num_users; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return 1; // Authentication successful
        }
    }
    return 0; // Authentication failed
}

void redirect(const char* url) {
    printf("Content-Type: text/html\n\n");
    printf("<html><head><meta http-equiv=\"refresh\" content=\"0;url=%s\"></head></html>", url);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    // Simulate receiving form data
    if (fgets(username, MAX_USERNAME_LENGTH, stdin) == NULL || fgets(password, MAX_PASSWORD_LENGTH, stdin) == NULL) {
        redirect("internal_server_error.html");
        return 1;
    }

    // Remove newline characters from input
    username[strcspn(username, "\n")] = '\0';
    password[strcspn(password, "\n")] = '\0';

    int auth_result = authenticate_user(username, password);

    if (auth_result == 1) {
        redirect("success.html");
    } else {
        redirect("cant_login.html");
    }

    return 0;
}