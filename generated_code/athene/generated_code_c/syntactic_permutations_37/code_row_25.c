#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 100
#define MAX_PASSWORD_LEN 100

typedef struct {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User database[] = {{"admin", "password123"}, {"user", "pass"}};
int db_size = sizeof(database) / sizeof(User);

void redirect(const char *url) {
    printf("Location: %s\n", url);
    printf("Content-Type: text/html\n\n");
}

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < db_size; i++) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void handle_login() {
    char username[MAX_USERNAME_LEN] = "";
    char password[MAX_PASSWORD_LEN] = "";

    if (getenv("CONTENT_LENGTH") != NULL) {
        int length = atoi(getenv("CONTENT_LENGTH"));
        fread(username, sizeof(char), MAX_USERNAME_LEN - 1, stdin);
        fread(password, sizeof(char), MAX_PASSWORD_LEN - 1, stdin);
        username[length] = '\0';
        password[length] = '\0';

        if (authenticate(username, password)) {
            redirect("/success");
        } else {
            redirect("/login?error=invalid_credentials");
        }
    } else {
        redirect("/internal_server_error");
    }
}

int main() {
    handle_login();
    return 0;
}