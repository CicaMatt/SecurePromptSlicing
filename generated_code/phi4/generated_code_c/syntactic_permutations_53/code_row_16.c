#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char username[50];
    int isAdmin;
} User;

User currentUser = {"", 0};

void redirectToLogin() {
    printf("Redirecting to login page...\n");
    // Code to redirect to the login page can be implemented here.
}

void redirectToUserPage() {
    printf("Redirecting to user page...\n");
    // Code to redirect to the user page can be implemented here.
}

void redirectToAdminPage() {
    printf("Redirecting to admin page...\n");
    // Code to redirect to the admin page can be implemented here.
}

int main() {
    if (currentUser.username[0] == '\0') {
        redirectToLogin();
    } else if (!currentUser.isAdmin) {
        redirectToUserPage();
    } else {
        redirectToAdminPage();
    }
    
    return 0;
}