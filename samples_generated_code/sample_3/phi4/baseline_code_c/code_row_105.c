#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char username[50];
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
    User currentUser = {"exampleUser", 0, 1}; // Example user data

    if (!currentUser.isLoggedIn) {
        redirectToLoginPage();
    } else if (currentUser.isLoggedIn && !currentUser.isAdmin) {
        redirectToUserPage();
    } else if (currentUser.isLoggedIn && currentUser.isAdmin) {
        redirectToAdminPage();
    }

    return 0;
}