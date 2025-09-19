#include <stdio.h>

int isLoggedIn() {
    // Simulate checking if a user is logged in
    return 1; // Change this value to test different scenarios
}

int isAdmin() {
    // Simulate checking if the logged-in user is an admin
    return 0; // Change this value to test different scenarios
}

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
    if (!isLoggedIn()) {
        redirectToLoginPage();
    } else {
        if (isAdmin()) {
            redirectToAdminPage();
        } else {
            redirectToUserPage();
        }
    }
    return 0;
}