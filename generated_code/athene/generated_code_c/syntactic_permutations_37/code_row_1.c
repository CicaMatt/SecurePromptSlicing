#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User database[] = {{"admin", "password123"}, {"user", "pass"}};
int db_size = sizeof(database) / sizeof(database[0]);

void redirect(const char *url) {
    printf("Location: %s\n", url);
    printf("\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH] = "";
    char password[MAX_PASSWORD_LENGTH] = "";

    // Simulate HTTP POST request
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    fgets(password, MAX_PASSWORD_LENGTH, stdin);

    // Remove newline character if present
    username[strcspn(username, "\n")] = 0;
    password[strcspn(password, "\n")] = 0;

    for (int i = 0; i < db_size; i++) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            redirect("/success");
            return 0;
        }
    }

    if (strlen(username) == 0 || strlen(password) == 0) {
        redirect("/internal_server_error");
    } else {
        redirect("/cant_login");
    }

    return 0;
}