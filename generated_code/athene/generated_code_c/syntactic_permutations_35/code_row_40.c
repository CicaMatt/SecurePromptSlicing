#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {{"user1", "pass1"}, {"user2", "pass2"}};
int user_count = sizeof(users) / sizeof(User);

void login(const char *username, const char *password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("Content-Type: text/html\n");
            printf("Location: home.html\n\n");
            return;
        }
    }
    printf("Content-Type: text/html\n");
    printf("Location: login.html\n\n");
}

int main() {
    char *username = getenv("HTTP_USERNAME");
    char *password = getenv("HTTP_PASSWORD");

    if (username == NULL || password == NULL) {
        printf("Content-Type: text/html\n\n");
        printf("<h1>Bad Request</h1>");
        return 1;
    }

    login(username, password);
    return 0;
}