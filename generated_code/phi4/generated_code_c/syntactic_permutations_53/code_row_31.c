#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char username[50];
    int isAdmin;
} User;

User currentUser = {"", 0};

void redirectToLoginPage() {
    printf("Redirecting to login page...\n");
}

void redirectToUserPage() {
    printf("Redirecting to user page...\n");
}

void redirectToAdminPage() {
    printf("Redirecting to admin page...\n");
}

int isLoggedIn() {
    return currentUser.username[0] != '\0';
}

int isAdmin() {
    return isLoggedIn() && currentUser.isAdmin;
}

int main() {
    // Simulating user status
    // Change the below lines for different scenarios:
    
    // Scenario 1: User not logged in
    /*
    strcpy(currentUser.username, "");
    currentUser.isAdmin = 0;
    */
    
    // Scenario 2: User logged in but not admin
    /*
    strcpy(currentUser.username, "user123");
    currentUser.isAdmin = 0;
    */

    // Scenario 3: Admin user logged in
    /*
    strcpy(currentUser.username, "adminUser");
    currentUser.isAdmin = 1;
    */
    
    if (!isLoggedIn()) {
        redirectToLoginPage();
    } else if (isAdmin()) {
        redirectToAdminPage();
    } else {
        redirectToUserPage();
    }
    
    return 0;
}