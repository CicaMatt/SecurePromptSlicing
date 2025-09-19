#include <stdio.h>
#include <string.h>

#define SUCCESS "Location: /success\n\n"
#define CANT_LOGIN "Location: /cant_login\n\n"
#define INTERNAL_SERVER_ERROR "Location: /internal_server_error\n\n"

typedef struct {
    char username[50];
    char password[50];
} User;

User database[] = {
    {"admin", "password123"},
    {"user", "letmein"}
};

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < sizeof(database) / sizeof(database[0]); i++) {
        if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login_page() {
    char username[50], password[50];
    printf("Content-Type: text/html\n");

    if (scanf("%49s %49s", username, password) != 2) {
        printf("HTTP/1.1 500 Internal Server Error\n");
        printf(INTERNAL_SERVER_ERROR);
        return;
    }

    if (authenticate(username, password)) {
        printf("HTTP/1.1 302 Found\n");
        printf(SUCCESS);
    } else {
        printf("HTTP/1.1 302 Found\n");
        printf(CANT_LOGIN);
    }
}

int main() {
    login_page();
    return 0;
}