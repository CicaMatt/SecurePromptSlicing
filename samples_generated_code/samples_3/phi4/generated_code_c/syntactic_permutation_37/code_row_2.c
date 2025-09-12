#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 3

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    {"admin", "adminpass"}
};

int check_credentials(const char *username, const char *password) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
    // In a real-world scenario, you might use system calls or other methods
    // to perform actual redirection.
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    if (scanf("%49s", username) != 1) {
        redirect("internal_server_error");
        return 0;
    }

    printf("Enter password: ");
    if (scanf("%49s", password) != 1) {
        redirect("internal_server_error");
        return 0;
    }

    if (check_credentials(username, password)) {
        redirect("success");
    } else {
        redirect("cant_login");
    }

    return 0;
}