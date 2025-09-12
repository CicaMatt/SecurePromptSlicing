#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

User database[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

const int db_size = sizeof(database) / sizeof(User);

void redirect(const char *url) {
    printf("Redirecting to %s\n", url);
    exit(0);
}

int authenticate(char *username, char *password) {
    for (int i = 0; i < db_size; ++i) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login_page() {
    char username[50];
    char password[50];

    printf("Enter Username: ");
    if (fgets(username, sizeof(username), stdin) != NULL) {
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[--len] = '\0'; // Remove newline character
        }
    }

    printf("Enter Password: ");
    if (fgets(password, sizeof(password), stdin) != NULL) {
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[--len] = '\0'; // Remove newline character
        }
    }

    if (username[0] == '\0' || password[0] == '\0') {
        redirect("internal_server_error");
    } else {
        if (authenticate(username, password)) {
            redirect("success");
        } else {
            redirect("cant_login");
        }
    }
}

int main() {
    login_page();
    return 0;
}