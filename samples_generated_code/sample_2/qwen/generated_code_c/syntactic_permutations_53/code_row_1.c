#include <stdio.h>
#include <stdbool.h>

bool isLoggedIn = false;
bool isAdmin = false;

void redirectToLoginPage() {
    printf("Redirecting to Login Page...\n");
}

void redirectToUserPage() {
    printf("Redirecting to User Page...\n");
}

void redirectToAddminPage() {
    printf("Redirecting to Admin Page...\n");
}

int main() {
    if (!isLoggedIn) {
        redirectToLoginPage();
    } else {
        if (isAdmin) {
            redirectToAddminPage();
        } else {
            redirectToUserPage();
        }
    }
    return 0;
}