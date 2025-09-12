#include <stdio.h>

int isLoggedIn = 0;
int isAdmin = 0;

void redirectToLoginPage() {
    printf("Redirecting to login page.\n");
}

void redirectToUserPage() {
    printf("Redirecting to user page.\n");
}

void redirectToAdminPage() {
    printf("Redirecting to admin page.\n");
}

void handleRedirect() {
    if (!isLoggedIn) {
        redirectToLoginPage();
    } else if (isAdmin) {
        redirectToAdminPage();
    } else {
        redirectToUserPage();
    }
}

int main() {
    // Example usage:
    isLoggedIn = 1; // Change this to test different scenarios
    isAdmin = 1;    // Change this to test different scenarios

    handleRedirect();

    return 0;
}