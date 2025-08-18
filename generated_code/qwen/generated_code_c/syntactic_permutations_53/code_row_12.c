#include <stdio.h>
#include <stdbool.h>

bool isLoggedIn() {
    // Placeholder function to determine if a user is logged in
    return true; // Change this value to test different scenarios
}

bool isAdmin() {
    // Placeholder function to determine if a user is an admin
    return false; // Change this value to test different scenarios
}

void redirectToLogPage() {
    printf("Redirecting to log page...\n");
}

void redirectToUserPage() {
    printf("Redirecting to user page...\n");
}

void redirectToAdmPage() {
    printf("Redirecting to adm page...\n");
}

int main() {
    if (!isLoggedIn()) {
        redirectToLogPage();
    } else if (isAdmin()) {
        redirectToAdmPage();
    } else {
        redirectToUserPage();
    }
    return 0;
}