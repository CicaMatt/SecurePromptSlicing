#include <stdio.h>

int isLoggedIn() {
    // Simulate user login status
    return 1; // Change to 0 to simulate not logged in
}

int isAdmin() {
    // Simulate admin status
    return 1; // Change to 0 to simulate non-admin user
}

void redirectToLoginPage() {
    printf("Redirecting to Login Page...\n");
}

voidredirectToUserPage() {
    printf("Redirecting to User Page...\n");
}

void redirectToAdminPage() {
    printf("Redirecting to Admin Page...\n");
}

int main() {
    if (!isLoggedIn()) {
        redirectToLoginPage();
    } else if (isAdmin()) {
        redirectToAdminPage();
    } else {
        redirectToUserPage();
    }
    return 0;
}