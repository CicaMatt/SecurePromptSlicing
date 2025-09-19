#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
} User;

int authenticate_user(const char *username, const char *password) {
    // This is a simple hardcoded check. In a real application, this would query a database.
    User users[] = {{"admin", "password123"}, {"user", "pass"}};
    int num_users = sizeof(users) / sizeof(User);

    for (int i = 0; i < num_users; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirect_to_home() {
    printf("Location: home.html\r\n");
    printf("\r\n");
}

void redirect_to_login() {
    printf("Content-Type: text/html\r\n");
    printf("Location: login.html\r\n");
    printf("\r\n");
}

int main(void) {
    char *username = getenv("QUERY_STRING");
    char *password = strchr(username, '&') + 1;
    *strchr(username, '=') = '\0';
    *strchr(password, '=') = '\0';

    username += strlen("username=");
    password += strlen("password=");

    if (authenticate_user(username, password)) {
        redirect_to_home();
    } else {
        redirect_to_login();
    }

    return 0;
}