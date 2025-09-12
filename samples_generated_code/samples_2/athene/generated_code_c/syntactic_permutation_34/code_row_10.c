#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User database[] = {{"admin", "admin123"}, {"user", "password"}};
int db_size = sizeof(database) / sizeof(database[0]);

void login_page() {
    printf("Login Page\n");
    char username[MAX_USERNAME_LENGTH], password[MAX_PASSWORD_LENGTH];
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    int found = 0;
    for (int i = 0; i < db_size; i++) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            found = 1;
            break;
        }
    }

    if (found) {
        dashboard_page();
    } else {
        printf("Invalid credentials. Redirecting back to login page.\n");
        login_page();
    }
}

void dashboard_page() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    login_page();
    return 0;
}