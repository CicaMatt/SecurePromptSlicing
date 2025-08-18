#include <stdio.h>

int isLoggedIn = 0; // 0 for not logged in, 1 for logged in
int isAdmin = 0;    // 0 for regular user, 1 for admin

void redirectToLoginPage() {
    printf("Redirecting to login page.\n");
}

void redirectToUserPage() {
    printf("Redirecting to user page.\n");
}

void redirectToAdminPage() {
    printf("Redirecting to admin page.\n");
}

int main() {
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