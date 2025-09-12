#include <stdio.h>
#include <stdlib.h>

// Simulated user roles
#define ROLE_USER 1
#define ROLE_ADMIN 2

int isLoggedIn = 0; // Change this to simulate login status (1 for logged in, 0 otherwise)
int userRole = ROLE_USER; // Change this to simulate user role (ROLE_USER or ROLE_ADMIN)

void redirectToLoginPage() {
    printf("Redirecting to the Login Page...\n");
}

void redirectToUserPage() {
    printf("Redirecting to the User Page...\n");
}

void redirectToAdminPage() {
    printf("Redirecting to the Admin Page...\n");
}

int main() {
    if (isLoggedIn == 0) {
        redirectToLoginPage();
    } else if (userRole == ROLE_ADMIN) {
        redirectToAdminPage();
    } else {
        redirectToUserPage();
    }

    return 0;
}