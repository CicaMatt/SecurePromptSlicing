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
    User currentUser = {"john_doe", 1, 1};

    if (!currentUser.isLoggedIn) {
        redirectToLoginPage();
        return 0;
    }

    if (currentUser.isAdmin) {
        redirectToAdminPage();
    } else {
        redirectToUserPage();
    }
    
    return 0;
}