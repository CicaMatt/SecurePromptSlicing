#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

typedef struct {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

int check_credentials(const char *username, const char *password) {
    // Mock database of users
    User users[] = {
        {"user1", "pass1"},
        {"user2", "pass2"}
    };
    int num_users = sizeof(users) / sizeof(users[0]);

    for (int i = 0; i < num_users; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirect(const char *url) {
    printf("Location: %s\n", url);
    printf("\n");
    exit(0);
}

int main() {
    const char *username = getenv("HTTP_USERNAME");
    const char *password = getenv("HTTP_PASSWORD");

    if (!username || !password) {
        redirect("/internal_server_error");
    }

    int result = check_credentials(username, password);

    if (result == 1) {
        redirect("/success");
    } else {
        redirect("/cant_login");
    }

    return 0;
}