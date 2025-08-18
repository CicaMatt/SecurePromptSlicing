#include <stdio.h>
#include <stdbool.h>

bool isLoggedIn = false;
bool isAdmin = false;

void redirectToLoginPage() {
    printf("Redirecting to Login Page...\n");
}

void redirectIfLoggedIn() {
    printf("Redirecting...\n");
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
        redirectIfLoggedIn();
    }
    return 0;
}