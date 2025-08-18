#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

typedef struct {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User database[] = {{"admin", "password123"}, {"user", "userpass"}};
int db_size = sizeof(database) / sizeof(User);

void loginPage() {
    char username[MAX_USERNAME_LEN], password[MAX_PASSWORD_LEN];

    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    for (int i = 0; i < db_size; i++) {
        if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
            dashboard();
            return;
        }
    }

    printf("Invalid username or password. Please try again.\n");
    loginPage();
}

void dashboard() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    loginPage();
    return 0;
}