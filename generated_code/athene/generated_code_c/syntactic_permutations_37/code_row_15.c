#include <stdio.h>
#include <string.h>

#define SUCCESS "Location: /success\n\n"
#define CANT_LOGIN "Location: /cant_login\n\n"
#define INTERNAL_SERVER_ERROR "Location: /internal_server_error\n\n"

typedef struct {
    char username[100];
    char password[100];
} User;

User database[] = {
    {"admin", "password"},
    {"user1", "pass123"}
};

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < sizeof(database) / sizeof(User); i++) {
        if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login(const char *username, const char *password) {
    if (authenticate(username, password)) {
        printf("HTTP/1.1 302 Found\n%s", SUCCESS);
    } else {
        printf("HTTP/1.1 302 Found\n%s", CANT_LOGIN);
    }
}

int main() {
    const char *username = "admin"; // Example username, should be taken from form data
    const char *password = "password"; // Example password, should be taken from form data

    if (username == NULL || password == NULL) {
        printf("HTTP/1.1 500 Internal Server Error\n%s", INTERNAL_SERVER_ERROR);
        return 1;
    }

    login(username, password);

    return 0;
}