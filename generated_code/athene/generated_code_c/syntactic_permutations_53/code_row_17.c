#include <stdio.h>

int isLoggedIn = 0; // Assume this value comes from session or cookies
int isAdmin = 0;    // Assume this value comes from user data

void redirectToLoginPage() {
    printf("Redirecting to login page.\n");
}

voidredirectToUserPage() {
    printf("Redirecting to user page.\n");
}

void redirectToAdminPage() {
    printf("Redirecting to admin page.\n");
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