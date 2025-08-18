#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int isLoggedIn;
    int isAdmin;
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
    // Example user states
    User exampleUser1 = {0, 0}; // Not logged in
    User exampleUser2 = {1, 0}; // Logged in as a regular user
    User exampleUser3 = {1, 1}; // Logged in as an admin

    User current_user;

    printf("Enter login status (1 for logged in, 0 for not logged in): ");
    scanf("%d", &current_user.isLoggedIn);
    
    if (!current_user.isLoggedIn) {
        redirectToLoginPage();
    } else {
        printf("Enter admin status (1 for admin, 0 for regular user): ");
        scanf("%d", &current_user.isAdmin);

        if (current_user.isAdmin) {
            redirectToAdminPage();
        } else {
            redirectToHomePage();
        }
    }

    return 0;
}