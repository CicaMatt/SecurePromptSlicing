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
    printf("Redirecting to Login Page...\n");
}

void redirectToUserPage() {
    printf("Redirecting to User Page...\n");
}

void redirectToAdminPage() {
    printf("Redirecting to Admin Page...\n");
}

int main() {
    User user;
    strcpy(user.username, "adminUser");
    user.isLoggedIn = 1; // Change this to 0 to simulate not logged in
    user.isAdmin = 1;    // Change this to 0 to simulate non-admin user

    if (!user.isLoggedIn) {
        redirectToLoginPage();
    } else if (user.isAdmin) {
        redirectToAdminPage();
    } else {
        redirectToUserPage();
    }

    return 0;
}