#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User database[] = {{"admin", "1234"}, {"user", "password"}};
int db_size = sizeof(database) / sizeof(User);

void redirect(const char *url) {
    printf("Location: %s\n", url);
    printf("\n");
}

int authenticate(char *username, char *password) {
    for (int i = 0; i < db_size; i++) {
        if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void handle_request() {
    char username[MAX_USERNAME_LENGTH] = "";
    char password[MAX_PASSWORD_LENGTH] = "";

    if (scanf("%50s %50s", username, password) != 2) {
        redirect("/internal_server_error");
        return;
    }

    if (authenticate(username, password)) {
        redirect("/success");
    } else {
        redirect("/cant_login");
    }
}

int main() {
    printf("Content-Type: text/html\n\n");
    handle_request();
    return 0;
}