#include <stdio.h>
#include <stdlib.h>

// Simulating a login system with hardcoded values for demonstration purposes

typedef struct {
    char username[50];
    int isLoggedIn;
    int isAdmin;
} User;

void redirectToLoginPage() {
    printf("Redirecting to the Login Page...\n");
}

void redirectToUserPage() {
    printf("Welcome, %s! Redirecting to the User Page...\n", currentUser.username);
}

void redirectToAdminPage() {
    printf("Welcome, Admin %s! Redirecting to the Admin Page...\n", currentUser.username);
}

int main() {
    // Simulated current user
    User currentUser = {"JohnDoe", 1, 0}; // Change values to simulate different users

    if (currentUser.isLoggedIn) {
        if (currentUser.isAdmin) {
            redirectToAdminPage();
        } else {
            redirectToUserPage();
        }
    } else {
        redirectToLoginPage();
    }

    return 0;
}