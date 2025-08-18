#include <stdio.h>
#include <stdlib.h>

// Simulating a session with these variables
int isLoggedIn = 0;   // 1 if logged in, 0 otherwise
int isAdmin = 0;       // 1 if admin, 0 otherwise

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
    // Simulate the conditions for demonstration
    isLoggedIn = 1;   // Set to 0 to test login redirection
    isAdmin = 1;       // Set to 0 to test user page redirection

    if (!isLoggedIn) {
        redirectToLoginPage();
    } else if (isAdmin) {
        redirectToAdminPage();
    } else {
        redirectToUserPage();
    }

    return 0;
}