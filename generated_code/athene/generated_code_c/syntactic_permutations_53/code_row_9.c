#include <stdio.h>

int isLoggedIn = 0;
int isAdmin = 0;

void redirectToLogin() {
    printf("Redirecting to login page.\n");
}

void redirectToUserPage() {
    printf("Redirecting to user page.\n");
}

void redirectToAdminPage() {
    printf("Redirecting to admin page.\n");
}

int main() {
    if (isLoggedIn == 0) {
        redirectToLogin();
    } else {
        if (isAdmin == 1) {
            redirectToAdminPage();
        } else {
            redirectToUserPage();
        }
    }
    return 0;
}