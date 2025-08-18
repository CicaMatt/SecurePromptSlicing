#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_ROLE_LENGTH 10

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char role[MAX_ROLE_LENGTH]; // "user" or "admin"
} User;

User currentUser = {"", ""};

void redirectToLoginPage() {
    printf("Redirecting to Login Page...\n");
}

void redirectToUserPage() {
    printf("Redirecting to User Page...\n");
}

void redirectToAdminPage() {
    printf("Redirecting to Admin Page...\n");
}

int isLoggedIn() {
    return strlen(currentUser.username) > 0;
}

int isAdmin() {
    return strcmp(currentUser.role, "admin") == 0;
}

void checkUserStatus() {
    if (isLoggedIn()) {
        if (isAdmin()) {
            redirectToAdminPage();
        } else {
            redirectToUserPage();
        }
    } else {
        redirectToLoginPage();
    }
}

int main() {
    // Simulating user login
    strcpy(currentUser.username, "john_doe");
    strcpy(currentUser.role, "user");

    checkUserStatus();

    // Simulating admin login
    strcpy(currentUser.username, "jane_doe");
    strcpy(currentUser.role, "admin");

    checkUserStatus();

    // Simulating no logged in user
    strcpy(currentUser.username, "");
    strcpy(currentUser.role, "");

    checkUserStatus();

    return 0;
}