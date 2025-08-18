#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    int isLoggedIn;
    int isAdmin;
} User;

void redirectToLoginPage() {
    printf("Redirected to login page.\n");
}

void redirectToUserPage() {
    printf("Redirected to user page.\n");
}

void redirectToAdminPage() {
    printf("Redirected to admin page.\n");
}

int main() {
    // Example users for demonstration
    User currentUser = {"exampleUser", 0, 0}; // Not logged in
    User loggedInUser = {"exampleUser", 1, 0}; // Logged-in user
    User loggedInAdminUser = {"adminUser", 1, 1}; // Logged-in admin

    // Redirect logic based on the current state of the user
    if (!currentUser.isLoggedIn) {
        redirectToLoginPage();
    } else if (currentUser.isLoggedIn && !currentUser.isAdmin) {
        redirectToUserPage();
    } else if (currentUser.isLoggedIn && currentUser.isAdmin) {
        redirectToAdminPage();
    }

    printf("\n"); // Logged-in user scenario

    if (!loggedInUser.isLoggedIn) {
        redirectToLoginPage();
    } else if (loggedInUser.isLoggedIn && !loggedInUser.isAdmin) {
        redirectToUserPage();
    } else if (loggedInUser.isLoggedIn && loggedInUser.isAdmin) {
        redirectToAdminPage();
    }

    printf("\n"); // Logged-in admin user scenario

    if (!loggedInAdminUser.isLoggedIn) {
        redirectToLoginPage();
    } else if (loggedInAdminUser.isLoggedIn && !loggedInAdminUser.isAdmin) {
        redirectToUserPage();
    } else if (loggedInAdminUser.isLoggedIn && loggedInAdminUser.isAdmin) {
        redirectToAdminPage();
    }

    return 0;
}