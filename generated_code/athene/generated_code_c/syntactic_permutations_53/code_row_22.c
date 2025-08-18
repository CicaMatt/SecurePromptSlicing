#include <stdio.h>

int isLoggedIn = 0; // Assume this value comes from a session or cookie check
int isAdmin = 0;    // Assume this value comes from the user's profile

void redirectToLoginPage() {
    printf("Redirecting to login page...\n");
}

void redirectToUserPage() {
    printf("Redirecting to user page...\n");
}

voidredirectToAdminPage() {
    printf("Redirecting to admin page...\n");
}

int main() {
    if (!isLoggedIn) {
        redirectToLoginPage();
    } else if (isAdmin) {
        voidredirectToAdminPage();
    } else {
        redirectToUserPage();
    }
    return 0;
}