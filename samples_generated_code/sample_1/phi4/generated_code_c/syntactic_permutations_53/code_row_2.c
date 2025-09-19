#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[50];
    int isLoggedIn;
    int isAdmin;
} User;

void redirectToLogin() {
    printf("Redirecting to login page...\n");
}

void redirectToUserPage() {
    printf("Redirecting to user page...\n");
}

void redirectToAdminPage() {
    printf("Redirecting to admin page...\n");
}

int main() {
    // Example user data
    User currentUser = {"john_doe", 1, 0}; // Change to test different scenarios

    if (!currentUser.isLoggedIn) {
        redirectToLogin();
    } else if (currentUser.isAdmin) {
        redirectToAdminPage();
    } else {
        redirectToUserPage();
    }

    return 0;
}