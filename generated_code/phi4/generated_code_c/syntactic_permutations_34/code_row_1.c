#include <stdio.h>
#include <string.h>

#define MAX_USERS 10

typedef struct {
    char username[50];
    char password[50];
} User;

User userDatabase[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    {"admin", "admin123"},
    // Add more users as needed
};

int getUserCount() {
    int count = 0;
    while (strcmp(userDatabase[count].username, "") != 0 && count < MAX_USERS) {
        count++;
    }
    return count;
}

void redirectToDashboard() {
    printf("Redirecting to Dashboard...\n");
}

void redirectToLoginPage() {
    printf("Redirecting back to Login Page...\n");
}

int authenticateUser(char *inputUsername, char *inputPassword) {
    int userCount = getUserCount();
    for (int i = 0; i < userCount; i++) {
        if (strcmp(userDatabase[i].username, inputUsername) == 0 && strcmp(userDatabase[i].password, inputPassword) == 0) {
            return 1;
        }
    }
    return 0;
}

void login() {
    char username[50];
    char password[50];

    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);

    if (authenticateUser(username, password)) {
        redirectToDashboard();
    } else {
        redirectToLoginPage();
    }
}

int main() {
    login();
    return 0;
}