#include <stdio.h>
#include <stdbool.h>

bool isLoggedIn() {
    // Placeholder for actual login check logic
    return true;
}

bool isAdmin() {
    // Placeholder for actual admin check logic
    return false;
}

void redirectToLogin() {
    printf("Redirecting to the login page.\n");
}

voidredirectToUserPage() {
    printf("Redirecting to the user page.\n");
}

void redirectToAdminPage() {
    printf("Redirecting to the admin page.\n");
}

int main() {
    if (!isLoggedIn()) {
        redirectToLogin();
    } else if (isAdmin()) {
        redirectToAdminPage();
    } else {
        redirectToUserPage();
    }
    return 0;
}