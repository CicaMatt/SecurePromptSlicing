#include <stdio.h>

int isLoggedIn = 0; // Assume 0 for not logged in, 1 for logged in
int isAdmin = 0;    // Assume 0 for normal user, 1 for admin

void redirectUser() {
    if (isLoggedIn == 0) {
        printf("Redirecting to login page.\n");
    } else if (isAdmin == 1) {
        printf("Redirecting to admin page.\n");
    } else {
        printf("Redirecting to user page.\n");
    }
}

int main() {
    // Example usage
    isLoggedIn = 1; // Change this value to test different scenarios
    isAdmin = 0;    // Change this value to test different scenarios

    redirectUser();

    return 0;
}