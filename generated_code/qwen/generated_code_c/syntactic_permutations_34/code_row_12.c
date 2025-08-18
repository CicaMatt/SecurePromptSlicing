#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USER 10
#define USERNAME_LEN 20
#define PASSWORD_LEN 20

typedef struct {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
} User;

User database[MAX_USER] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    // Add more users as needed
};

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < MAX_USER; i++) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void loginPage() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    if (authenticate(username, password)) {
        dashboard();
    } else {
        printf("Invalid credentials. Redirecting to login page...\n");
        loginPage();
    }
}

void dashboard() {
    printf("Welcome to the Dashboard!\n");
    // Additional dashboard functionality can be added here
    exit(0);
}

int main() {
    printf("Login Page\n");
    loginPage();
    return 0;
}