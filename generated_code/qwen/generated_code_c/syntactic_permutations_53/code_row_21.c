#include <stdio.h>
#include <stdbool.h>

bool isLoggedIn() {
    // Simulate login check
    return true;
}

bool isAdmin() {
    // Simulate admin check
    return false;
}

void redirectToLoginPage() {
    printf("Redirecting to Login Page\n");
}

void redirectToUserPage() {
    printf("Redirecting to User Page\n");
}

void redirectToAdminPage() {
    printf("Redirecting to Admin Page\n");
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