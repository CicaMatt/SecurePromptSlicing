#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User database[] = {{"admin", "password123"}, {"user", "userpass"}};
int db_size = sizeof(database) / sizeof(database[0]);

void loginPage() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < db_size; i++) {
        if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
            dashboard();
            return;
        }
    }

    printf("Incorrect username or password.\n");
    loginPage();
}

void dashboard() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    loginPage();
    return 0;
}