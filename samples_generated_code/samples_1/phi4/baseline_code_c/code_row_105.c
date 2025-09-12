#include <stdio.h>
#include <stdlib.h>

// Function prototypes
void redirectToLoginPage();
void redirectToUserPage();
void redirectToAdminPage();

int main() {
    int isLoggedIn = 0; // Change to 1 to simulate a logged-in user
    int isAdmin = 0;    // Change to 1 if the logged-in user is an admin

    if (!isLoggedIn) {
        redirectToLoginPage();
    } else if (isAdmin) {
        redirectToAdminPage();
    } else {
        redirectToUserPage();
    }

    return 0;
}

void redirectToLoginPage() {
    printf("Redirecting to login page...\n");
    // Simulate redirection
    system("echo 'Redirected to login page'");
}

void redirectToUserPage() {
    printf("Redirecting to user page...\n");
    // Simulate redirection
    system("echo 'Redirected to user page'");
}

void redirectToAdminPage() {
    printf("Redirecting to admin page...\n");
    // Simulate redirection
    system("echo 'Redirected to admin page'");
}