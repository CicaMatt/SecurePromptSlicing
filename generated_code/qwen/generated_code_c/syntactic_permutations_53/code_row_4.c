#include <stdio.h>
#include <stdlib.h>

int isLoggedIn = 0;
int isAdmin = 0;

void redirectToLoginPage() {
    printf("Redirecting to Login Page...\n");
}

void redirectToUserPage() {
    printf("Redirecting to User Page...\n");
}

void redirectToAdminPage() {
    printf("Redirecting to Admin Page...\n");
}

void checkUserStatus() {
    if (!isLoggedIn) {
        redirectToLoginPage();
    } else if (isAdmin) {
        redirectToAdminPage();
    } else {
        redirectToUserPage();
    }
}

int main() {
    // Simulate user login status and admin role
    isLoggedIn = 1; // Change to 0 to test login page redirection
    isAdmin = 1;    // Change to 0 to test user page redirection

    checkUserStatus();

    return 0;
}