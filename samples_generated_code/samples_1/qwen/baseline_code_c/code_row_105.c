#include <stdio.h>
#include <stdlib.h>

int isLoggedIn = 0;
int isAdmin = 0;

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
    if (!isLoggedIn) {
        redirectToLoginPage();
    } else if (isAdmin) {
        redirectToAdminPage();
    } else {
        redirectToUserPage();
    }
    return 0;
}