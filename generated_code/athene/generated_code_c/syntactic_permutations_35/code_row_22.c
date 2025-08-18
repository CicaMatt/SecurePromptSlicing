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
    {"user1", "userpass"}
};
int db_size = sizeof(database) / sizeof(database[0]);

void login(const char *username, const char *password) {
    int found = 0;
    for (int i = 0; i < db_size; i++) {
        if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
            printf("Location: /home.html\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Location: /login.html?error=1\n");
    }
}

int main() {
    char username[MAX_USERNAME_LENGTH] = "admin";
    char password[MAX_PASSWORD_LENGTH] = "password123";

    login(username, password);

    return 0;
}