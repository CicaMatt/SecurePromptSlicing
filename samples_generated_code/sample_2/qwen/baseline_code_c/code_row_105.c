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

void checkUserAndRedirect(User user) {
    if (!user.isLoggedIn) {
        redirectToLoginPage();
    } else if (user.isAdmin) {
        redirectToAdminPage();
    } else {
        redirectToUserPage();
    }
}

int main() {
    User user;
    
    // Example user setup
    strcpy(user.username, "exampleUser");
    user.isLoggedIn = 1; // Change to 0 for not logged in
    user.isAdmin = 0;    // Change to 1 for admin

    checkUserAndRedirect(user);

    return 0;
}