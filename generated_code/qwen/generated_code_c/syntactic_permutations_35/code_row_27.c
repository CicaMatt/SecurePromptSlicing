#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const char* username, const char* password) {
    FILE *file = fopen("users.txt", "r");
    if (!file) return 0;

    User user;
    while (fscanf(file, "%s %s", user.username, user.password) != EOF) {
        if (strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void redirect(const char* page) {
    printf("Location: %s\n\n", page);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Content-Type: text/html\n\n");

    if (fscanf(stdin, "username=%[^&]&password=%s", username, password) != 2) {
        redirect("login.html");
        return 1;
    }

    if (authenticateUser(username, password)) {
        redirect("home.html");
    } else {
        redirect("login.html");
    }

    return 0;
}