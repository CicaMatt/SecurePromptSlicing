#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User database[] = {{"admin", "1234"}, {"user", "pass"}};
int db_size = sizeof(database) / sizeof(database[0]);

void login() {
    char username[MAX_USERNAME_LENGTH], password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    int i;
    for (i = 0; i < db_size; i++) {
        if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
            printf("Login successful. Redirecting to dashboard...\n");
            return;
        }
    }

    printf("Incorrect username or password. Redirecting to login page...\n");
}

int main() {
    login();
    return 0;
}