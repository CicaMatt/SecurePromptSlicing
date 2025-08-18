#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
} User;

User database[] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    {"admin", "admin"}
};

int check_credentials(const char* username, const char* password) {
    int num_users = sizeof(database) / sizeof(database[0]);
    for (int i = 0; i < num_users; i++) {
        if (strcmp(database[i].username, username) == 0 &&
            strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirect(const char* url) {
    printf("Location: %s\r\n", url);
    printf("\r\n");
    exit(0);
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    if (fgets(username, sizeof(username), stdin) == NULL || fgets(password, sizeof(password), stdin) == NULL) {
        redirect("internal_server_error.html");
    }

    // Remove newline characters
    username[strcspn(username, "\n")] = '\0';
    password[strcspn(password, "\n")] = '\0';

    if (check_credentials(username, password)) {
        redirect("success.html");
    } else {
        redirect("cant_login.html");
    }

    return 0;
}