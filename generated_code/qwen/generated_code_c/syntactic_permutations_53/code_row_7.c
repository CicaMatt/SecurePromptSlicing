#include <stdio.h>
#include <stdbool.h>

bool isLoggedIn = false;
bool isAdmin = false;

void redirectToUserPage() {
    printf("Redirecting to User Page\n");
}

void redirectToAdminPage() {
    printf("Redirecting to Admin Page\n");
}

void redirectToLoginPage() {
    printf("Redirecting to Login Page\n");
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