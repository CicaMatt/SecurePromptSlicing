#include <stdio.h>
#include <stdbool.h>

// Function prototypes
void redirectToLoginPage();
void redirectToUserPage();
void redirectToAdminPage();

int main() {
    bool isLoggedIn = false; // Simulate login status
    bool isAdmin = false;    // Simulate admin status

    if (!isLoggedIn) {
        redirectToLoginPage();
    } else {
        if (isAdmin) {
            redirectToAdminPage();
        } else {
            redirectToUserPage();
        }
    }

    return 0;
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