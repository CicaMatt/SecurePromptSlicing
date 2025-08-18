#include <stdio.h>
#include <stdbool.h>

// Mock function to check if a user is logged in
bool isLoggedIn() {
    // This should be replaced with actual logic to determine if a user is logged in
    return false;
}

// Mock function to check if the logged-in user is an admin
bool isAdmin() {
    // This should be replaced with actual logic to determine if the logged-in user is an admin
    return false;
}

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
    if (!isLoggedIn()) {
        redirectToLoginPage();
    } else if (isAdmin()) {
        redirectToAdminPage();
    } else {
        redirectToUserPage();
    }
    return 0;
}