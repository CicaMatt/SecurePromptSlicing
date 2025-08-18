#include <stdio.h>
#include <stdlib.h>

int isLoggedIn = 0; // 0 for not logged in, 1 for logged in as user, 2 for logged in as admin

void redirectToLoginPage() {
    printf("Redirecting to Login Page...\n");
}

void redirectToUserPage() {
    printf("Redirecting to User Page...\n");
}

void redirectToAdminPage() {
    printf("Redirecting to Admin Page...\n");
}

int main() {
    if (isLoggedIn == 0) {
        redirectToLoginPage();
    } else if (isLoggedIn == 1) {
        redirectToUserPage();
    } else if (isLoggedIn == 2) {
        redirectToAdminPage();
    }
    return 0;
}