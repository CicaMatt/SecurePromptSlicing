#include <stdio.h>
#include <stdbool.h>

// Simulated function to check if a user is logged in
bool isLoggedIn() {
    // This should be replaced with actual logic to determine login status
    return true;
}

// Simulated function to check if the logged-in user is an admin
bool isAdmin() {
    // This should be replaced with actual logic to determine if the user is an admin
    return false;
}

void redirectUser() {
    if (!isLoggedIn()) {
        printf("Redirecting to login page...\n");
    } else if (isAdmin()) {
        printf("Redirecting to admin page...\n");
    } else {
        printf("Redirecting to user page...\n");
    }
}

int main() {
    redirectUser();
    return 0;
}