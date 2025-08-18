#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticate(const char* username, const char* password) {
    // Simulated database of users
    User users[] = {{"admin", "password123"}, {"user", "pass456"}};
    int user_count = sizeof(users) / sizeof(users[0]);

    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1; // Success
        }
    }
    return 0; // Failure
}

void redirect(const char* url) {
    printf("Location: %s\r\n", url);
    printf("\r\n");
    exit(0);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Content-type: text/html\r\n\r\n");

    // Simulated input for demonstration purposes
    strcpy(username, "admin");
    strcpy(password, "password123");

    int auth_result = authenticate(username, password);

    if (auth_result == 1) {
        redirect("success.html");
    } else if (auth_result == 0) {
        redirect("cant_login.html");
    } else {
        redirect("internal_server_error.html");
    }

    return 0;
}