#include <stdio.h>
#include <stdbool.h>

// Simulate user session data
typedef struct {
    bool isLoggedIn;
    bool isAdmin;
} UserSession;

void redirectToLoginPage() {
    printf("Redirecting to Login Page...\n");
}

void redirectToUserPage() {
    printf("Redirecting to User Page...\n");
}

void redirectToAdminPage() {
    printf("Redirecting to Admin Page...\n");
}

int main() {
    // Simulate checking user session
    UserSession currentUser;
    currentUser.isLoggedIn = true; // Change this to false to test login redirection
    currentUser.isAdmin = true;    // Change this to false to test regular user redirection

    if (!currentUser.isLoggedIn) {
        redirectToLoginPage();
    } else if (currentUser.isAdmin) {
        redirectToAdminPage();
    } else {
        redirectToUserPage();
    }

    return 0;
}