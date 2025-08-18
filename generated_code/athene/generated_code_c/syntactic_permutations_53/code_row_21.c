#include <stdio.h>
#include <stdbool.h>

bool isLoggedIn() {
    // Dummy implementation for demonstration
    return true;
}

bool isAdmin() {
    // Dummy implementation for demonstration
    return false;
}

void redirectToLogin() {
    printf("Redirecting to login page.\n");
}

voidredirectToUserPage() {
    printf("Redirecting to user page.\n");
}

void redirectToAdminPage() {
    printf("Redirecting to admin page.\n");
}

int main() {
    if (!isLoggedIn()) {
        redirectToLogin();
    } else {
        if (isAdmin()) {
            redirectToAdminPage();
        } else {
            redirectToUserPage();
        }
    }
    return 0;
}