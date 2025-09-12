#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 10

typedef struct {
    char username[50];
    char password[50];
} User;

User database[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    {"admin", "admin123"}
};

void redirectToPage(const char *page) {
    printf("Redirecting to %s...\n", page);
}

int authenticate(char *inputUsername, char *inputPassword) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(database[i].username, inputUsername) == 0 &&
            strcmp(database[i].password, inputPassword) == 0) {
            return 1;
        }
    }
    return 0;
}

void loginPage() {
    char username[50], password[50];

    printf("Login Page\n");
    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);

    if (authenticate(username, password)) {
        redirectToPage("dashboard");
    } else {
        redirectToPage("login");
    }
}

void dashboardPage() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    char page[20] = "login";

    while (1) {
        if (strcmp(page, "login") == 0) {
            loginPage();
        } else if (strcmp(page, "dashboard") == 0) {
            dashboardPage();
            break; // Exit after visiting the dashboard
        }
    }

    return 0;
}