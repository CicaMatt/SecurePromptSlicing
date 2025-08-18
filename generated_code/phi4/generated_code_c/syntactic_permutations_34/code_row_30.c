#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 5

typedef struct {
    char username[50];
    char password[50];
} User;

User database[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    {"user3", "pass3"},
    {"user4", "pass4"},
    {"user5", "pass5"}
};

void redirectToPage(const char* page) {
    printf("Redirecting to %s...\n", page);
}

int authenticate(char* username, char* password) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login() {
    char enteredUsername[50];
    char enteredPassword[50];

    printf("Login Page\n");
    printf("Enter Username: ");
    scanf("%49s", enteredUsername);
    printf("Enter Password: ");
    scanf("%49s", enteredPassword);

    if (authenticate(enteredUsername, enteredPassword)) {
        redirectToPage("Dashboard");
    } else {
        redirectToPage("Login");
    }
}

int main() {
    login();
    return 0;
}