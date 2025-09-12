#include <stdio.h>

int isLoggedIn = 0;
int isAdmin = 0;

void redirectToLoginPage() {
    printf("Redirecting to login page...\n");
}

void redirectToUserPage() {
    printf("Redirecting to user page...\n");
}

void redirectToAdminPage() {
    printf("Redirecting to admin page...\n");
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