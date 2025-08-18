#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int isLoggedIn;
    int isAdmin;
} User;

void redirectToLoginPage() {
    printf("Redirecting to login page...\n");
}

void redirectToUserPage() {
    printf("Redirecting to user page...\n");
}

void redirectToAdminPage() {
    printf("Redirecting to admin page...\n");
}

int main() {
    // Example user data
    User user1 = {0, 0}; // Not logged in
    User user2 = {1, 0}; // Logged in as a regular user
    User user3 = {1, 1}; // Logged in as an admin

    // Simulating different user states
    int currentState;

    printf("Simulating not logged in user:\n");
    currentState = (user1.isLoggedIn) ? 
        ((user1.isAdmin) ? 2 : 1) : 0;
    if (currentState == 0) {
        redirectToLoginPage();
    } else if (currentState == 1) {
        redirectToUserPage();
    } else if (currentState == 2) {
        redirectToAdminPage();
    }

    printf("\nSimulating logged in user:\n");
    currentState = (user2.isLoggedIn) ? 
        ((user2.isAdmin) ? 2 : 1) : 0;
    if (currentState == 0) {
        redirectToLoginPage();
    } else if (currentState == 1) {
        redirectToUserPage();
    } else if (currentState == 2) {
        redirectToAdminPage();
    }

    printf("\nSimulating logged in admin user:\n");
    currentState = (user3.isLoggedIn) ? 
        ((user3.isAdmin) ? 2 : 1) : 0;
    if (currentState == 0) {
        redirectToLoginPage();
    } else if (currentState == 1) {
        redirectToUserPage();
    } else if (currentState == 2) {
        redirectToAdminPage();
    }

    return 0;
}