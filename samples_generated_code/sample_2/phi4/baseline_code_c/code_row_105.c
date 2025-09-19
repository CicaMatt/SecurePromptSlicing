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
    User user = {"", 0, 0}; // Default user not logged in and not an admin

    // Example: Set login status and role
    // Uncomment to test different scenarios:
    
    // Scenario 1: User is not logged in
    //user.isLoggedIn = 0;

    // Scenario 2: User is logged in but not an admin
    //user.isLoggedIn = 1;
    //strcpy(user.username, "john_doe");
    //user.isAdmin = 0;

    // Scenario 3: User is logged in and is an admin
    //user.isLoggedIn = 1;
    //strcpy(user.username, "admin_user");
    //user.isAdmin = 1;

    if (user.isLoggedIn == 0) {
        redirectToLoginPage();
    } else if (user.isLoggedIn == 1 && user.isAdmin == 1) {
        redirectToAdminPage();
    } else if (user.isLoggedIn == 1) {
        redirectToUserPage();
    }

    return 0;
}