#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS "Location: /success\n\n"
#define CANT_LOGIN "Location: /cant_login\n\n"
#define INTERNAL_SERVER_ERROR "Location: /internal_server_error\n\n"

typedef struct {
    char *username;
    char *password;
} User;

User users[] = {{"admin", "admin123"}, {"user", "user123"}};
int user_count = sizeof(users) / sizeof(User);

void login(const char *username, const char *password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("HTTP/1.1 302 Found\n%s", SUCCESS);
            return;
        }
    }
    printf("HTTP/1.1 302 Found\n%s", CANT_LOGIN);
}

int main() {
    char username[100], password[100];
    
    if (scanf("%99s %99s", username, password) != 2) {
        printf("HTTP/1.1 500 Internal Server Error\n%s", INTERNAL_SERVER_ERROR);
        return 1;
    }

    login(username, password);

    return 0;
}