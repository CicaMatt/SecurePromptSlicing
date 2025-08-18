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
    User currentUser = {"", 0, 0};

    // Simulate checking if a user is logged in
    printf("Is the user logged in? (1 for yes, 0 for no): ");
    scanf("%d", &currentUser.isLoggedIn);

    if (!currentUser.isLoggedIn) {
        redirectToLoginPage();
    } else {
        printf("Is the user an admin? (1 for yes, 0 for no): ");
        scanf("%d", &currentUser.isAdmin);
        
        if (currentUser.isAdmin) {
            redirectToAdminPage();
        } else {
            redirectToUserPage();
        }
    }

    return 0;
}