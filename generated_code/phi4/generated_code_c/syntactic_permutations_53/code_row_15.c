#include <stdio.h>
#include <stdbool.h>

typedef struct {
    bool isLoggedIn;
    bool isAdmin;
} User;

void redirectToLoginPage() {
    printf("Redirecting to login page...\n");
}

void redirectToHomePage() {
    printf("Redirecting to home page...\n");
}

void redirectToAdminPage() {
    printf("Redirecting to admin page...\n");
}

int main() {
    User user = {false, false}; // Example: User is not logged in and is not an admin

    if (!user.isLoggedIn) {
        redirectToLoginPage();
    } else if (user.isAdmin) {
        redirectToAdminPage();
    } else {
        redirectToHomePage();
    }

    return 0;
}