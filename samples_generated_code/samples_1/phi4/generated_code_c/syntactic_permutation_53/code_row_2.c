#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int isLoggedIn;
    int isAdmin;
} User;

void redirectToLoginPage() {
    printf("Redirecting to Login Page...\n");
}

void redirectToUserPage() {
    printf("Redirecting to User Page...\n");
}

void redirectToAdminPage() {
    printf("Redirecting to Admin Page...\n");
}

int main() {
    User user = {1, 0}; // Example user who is logged in but not an admin

    if (!user.isLoggedIn) {
        redirectToLoginPage();
    } else if (user.isAdmin) {
        redirectToAdminPage();
    } else {
        redirectToUserPage();
    }

    return 0;
}