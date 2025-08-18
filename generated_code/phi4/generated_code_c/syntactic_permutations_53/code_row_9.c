#include <stdio.h>
#include <stdbool.h>

// Mock functions for demonstration purposes
bool isLoggedIn() {
    // Placeholder: check login status
    return true;  // Change this value as needed for testing
}

bool isAdmin() {
    // Placeholder: check if user is an admin
    return false; // Change this value as needed for testing
}

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
    if (!isLoggedIn()) {
        redirectToLoginPage();
    } else if (isAdmin()) {
        redirectToAdminPage();
    } else {
        redirectToUserPage();
    }
    return 0;
}