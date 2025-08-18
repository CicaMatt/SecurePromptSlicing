#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User database[] = {
    {"admin", "password123"},
    {"user", "pass456"}
};

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < sizeof(database) / sizeof(database[0]); i++) {
        if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirect(const char *location) {
    printf("Location: %s\n", location);
    printf("Content-Type: text/html\n\n");
    printf("<html><body><p>Redirecting to <a href=\"%s\">%s</a></p></body></html>", location, location);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    if (fgets(username, MAX_USERNAME_LENGTH, stdin) == NULL || fgets(password, MAX_PASSWORD_LENGTH, stdin) == NULL) {
        redirect("/internal_server_error");
        return 1;
    }

    // Remove newline characters
    username[strcspn(username, "\n")] = 0;
    password[strcspn(password, "\n")] = 0;

    if (authenticate(username, password)) {
        redirect("/success");
    } else {
        redirect("/cant_login");
    }

    return 0;
}