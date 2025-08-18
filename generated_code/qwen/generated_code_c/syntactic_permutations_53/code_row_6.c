#include <stdio.h>
#include <stdbool.h>

// Function prototypes
bool isLoggedIn();
bool isAdmin();

int main() {
    if (!isLoggedIn()) {
        printf("Redirecting to login page...\n");
    } else if (isAdmin()) {
        printf("Redirecting to admin page...\n");
    } else {
        printf("Redirecting to user page...\n");
    }
    return 0;
}

// Mock function to simulate login status
bool isLoggedIn() {
    // This should check the actual login status, for example from session data or a database
    return true; // Simulating logged in state
}

// Mock function to simulate admin status
bool isAdmin() {
    // This should check if the user has admin privileges
    return false; // Simulating non-admin state
}