#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User database[] = {
    {"admin", "password123"},
    {"user1", "pass456"}
};

int authenticate(const char *username, const char *password) {
    for (size_t i = 0; i < sizeof(database) / sizeof(database[0]); i++) {
        if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirect(const char *location) {
    printf("Location: %s\n", location);
    printf("\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH] = "";
    char password[MAX_PASSWORD_LENGTH] = "";

    // Simulate form data (for simplicity)
    if (scanf("%50s %50s", username, password) != 2) {
        redirect("/internal_server_error");
        return 1;
    }

    if (authenticate(username, password)) {
        redirect("/success");
    } else {
        printf("Status: 401 Unauthorized\n");
        printf("\n");
        printf("<h1>Unauthorized</h1>");
    }

    return 0;
}