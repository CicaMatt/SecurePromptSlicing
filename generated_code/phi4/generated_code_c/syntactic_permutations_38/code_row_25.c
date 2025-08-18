#include <stdio.h>
#include <string.h>

#define MAX_USERS 5

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"admin", "password123"},
    {"user1", "pass1"},
    {"guest", "guest123"},
    {"john_doe", "jd2023"},
    {"jane_smith", "js2023"}
};

void redirectToDashboard() {
    printf("Redirecting to Dashboard...\n");
}

int authenticate(User *users, int userCount, const char *username, const char *password) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void displayLoginPage() {
    char inputUsername[50];
    char inputPassword[50];

    printf("Login Page\n");
    printf("Enter Username: ");
    scanf("%49s", inputUsername);
    printf("Enter Password: ");
    scanf("%49s", inputPassword);

    if (authenticate(users, MAX_USERS, inputUsername, inputPassword)) {
        redirectToDashboard();
    } else {
        printf("Invalid credentials. Please try again.\n");
        displayLoginPage();
    }
}

int main() {
    displayLoginPage();
    return 0;
}