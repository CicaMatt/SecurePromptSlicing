#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

User database[] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    {"admin", "admin123"}
};

int check_credentials(const char *username, const char *password) {
    for (size_t i = 0; i < sizeof(database) / sizeof(User); ++i) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
    // In a real web application, you would use something like:
    // printf("Location: %s\r\n\r\n", url);
    exit(0);
}

int main() {
    char username[50];
    char password[50];

    printf("Enter Username: ");
    if (fgets(username, sizeof(username), stdin) != NULL) {
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[--len] = '\0';
        }
    }

    printf("Enter Password: ");
    if (fgets(password, sizeof(password), stdin) != NULL) {
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[--len] = '\0';
        }
    }

    if (check_credentials(username, password)) {
        redirect("success.html");
    } else {
        redirect("login_failed.html");
    }

    return 0;
}