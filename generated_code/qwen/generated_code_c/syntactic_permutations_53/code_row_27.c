#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
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
    User currentUser = {"exampleUser", 1, 0}; // Example user data: username, isLoggedIn, isAdmin

    if (!currentUser.isLoggedIn) {
        redirectToLoginPage();
    } else if (currentUser.isAdmin) {
        redirectToAdminPage();
    } else {
        redirectToUserPage();
    }

    return 0;
}