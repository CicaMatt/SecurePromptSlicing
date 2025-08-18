#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User database[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};
int num_users = sizeof(database) / sizeof(User);

int authenticate(const char* username, const char* password) {
    for (int i = 0; i < num_users; ++i) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirect(const char* url) {
    printf("Redirecting to: %s\n", url);
    // In a real web application, you would use HTTP headers for redirection
    // printf("Location: %s\r\n\r\n", url);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    if (fgets(username, sizeof(username), stdin) != NULL) {
        username[strcspn(username, "\n")] = '\0'; // Remove newline character
    } else {
        redirect("internal_server_error");
        return 1;
    }

    printf("Enter your password: ");
    if (fgets(password, sizeof(password), stdin) != NULL) {
        password[strcspn(password, "\n")] = '\0'; // Remove newline character
    } else {
        redirect("internal_server_error");
        return 1;
    }

    if (authenticate(username, password)) {
        redirect("success");
    } else {
        redirect("cant_login");
    }

    return 0;
}