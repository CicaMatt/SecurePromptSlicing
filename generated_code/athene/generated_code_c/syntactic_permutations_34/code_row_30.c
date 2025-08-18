#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define DATABASE_SIZE 10

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User database[DATABASE_SIZE] = {
    {"user1", "password1"},
    {"user2", "password2"},
    // Add more users as needed
};

void loginPage() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    scanf("%49s", username);
    printf("Enter your password: ");
    scanf("%49s", password);

    for (int i = 0; i < DATABASE_SIZE; i++) {
        if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
            dashboardPage();
            return;
        }
    }

    printf("Invalid username or password. Please try again.\n");
    loginPage();
}

void dashboardPage() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    loginPage();
    return 0;
}