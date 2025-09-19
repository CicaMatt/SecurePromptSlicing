#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

int authenticate(const char* username, const char* password) {
    for (int i = 0; i < sizeof(database) / sizeof(User); i++) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirect(const char* url) {
    printf("Redirecting to: %s\n", url);
    exit(0);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter Username: ");
    if (fgets(username, MAX_USERNAME_LENGTH, stdin) != NULL) {
        // Remove newline character from input
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }
    }

    printf("Enter Password: ");
    if (fgets(password, MAX_PASSWORD_LENGTH, stdin) != NULL) {
        // Remove newline character from input
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[len - 1] = '\0';
        }
    }

    int result;
    if ((result = authenticate(username, password)) < 0) {
        redirect("internal_server_error");
    } else if (result) {
        redirect("success");
    } else {
        redirect("cant_login");
    }

    return 0;
}