#include <stdio.h>

int isLoggedIn = 0;
int isAdmin = 0;

void redirectToLoginPage() {
    printf("Redirecting to login page...\n");
}

void redirectToUserPage() {
    printf("Redirecting to user page...\n");
}

void redirectToAdminPage() {
    printf("Redirecting to admin page...\n");
}

void handleRedirection() {
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
    isLoggedIn = 1; // Set to 1 when user is logged in
    isAdmin = 0;    // Set to 1 when user is admin

    handleRedirection();

    return 0;
}