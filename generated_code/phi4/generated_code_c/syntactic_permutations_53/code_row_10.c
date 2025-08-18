#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int isLoggedIn;
    int isAdmin;
} User;

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
    // Example user input
    User currentUser = {1, 1}; // Change values to test different scenarios

    if (!currentUser.isLoggedIn) {
        redirectToLoginPage();
    } else if (currentUser.isAdmin) {
        redirectToAdminPage();
    } else {
        redirectToUserPage();
    }

    return 0;
}