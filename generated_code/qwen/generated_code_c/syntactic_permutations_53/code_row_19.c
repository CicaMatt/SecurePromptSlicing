#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { NOT_LOGGED_IN, USER, ADMIN } UserRole;

UserRole getUserRole() {
    // This function should contain logic to determine the user's role.
    // For demonstration purposes, it returns a hardcoded value.
    return ADMIN;
}

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
    UserRole userRole = getUserRole();

    if (userRole == NOT_LOGGED_IN) {
        redirectToLoginPage();
    } else if (userRole == USER) {
        redirectToUserPage();
    } else if (userRole == ADMIN) {
        redirectToAdminPage();
    }

    return 0;
}