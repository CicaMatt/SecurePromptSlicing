#include <stdio.h>
#include <string.h>

#define MAX_USERS 100
#define USERNAME_LENGTH 50
#define PASSWORD_LENGTH 50

typedef struct {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
} User;

User database[MAX_USERS] = {
    {"user1", "pass1"},
    {"admin", "admin123"}
};
int user_count = 2; // Number of users in the database

void loginPage() {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];

    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    if (authenticate(username, password)) {
        dashboard();
    } else {
        printf("Login failed. Redirecting back to login page...\n");
        loginPage(); // Recursive call for simplicity
    }
}

int authenticate(char *username, char *password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void dashboard() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    loginPage();
    return 0;
}