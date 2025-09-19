#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS];
int userCount = 0;

void loadUsers() {
    // Simulating database records
    strcpy(users[userCount].username, "user1");
    strcpy(users[userCount].password, "pass1");
    userCount++;

    strcpy(users[userCount].username, "user2");
    strcpy(users[userCount].password, "pass2");
    userCount++;
}

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirectTo(const char *url) {
    printf("Redirecting to %s\n", url);
}

int main() {
    loadUsers();

    char username[50];
    char password[50];

    // Simulating input from login form
    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    if (authenticate(username, password)) {
        redirectTo("home.html");
    } else {
        redirectTo("login.html");
    }

    return 0;
}