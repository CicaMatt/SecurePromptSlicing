#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User database[] = {{"admin", "password123"}, {"user", "pass"}};
int user_count = sizeof(database) / sizeof(database[0]);

void login_page() {
    char username[MAX_USERNAME_LENGTH], password[MAX_PASSWORD_LENGTH];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < user_count; i++) {
        if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
            dashboard_page();
            return;
        }
    }

    printf("Invalid username or password. Please try again.\n");
    login_page();
}

void dashboard_page() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    login_page();
    return 0;
}