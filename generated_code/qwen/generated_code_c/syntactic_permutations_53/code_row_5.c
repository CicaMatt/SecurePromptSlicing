#include <stdio.h>
#include <stdlib.h>

int main() {
    int isLoggedIn = 1; // Change this value for testing (0 for not logged in, 1 for logged in)
    int isAdmin = 0;    // Change this value for testing (0 for not admin, 1 for admin)

    if (!isLoggedIn) {
        printf("Redirecting to login page...\n");
        // Simulate redirection
        exit(0);
    } else if (isAdmin) {
        printf("Redirecting to admin page...\n");
        // Simulate redirection
        exit(0);
    } else {
        printf("Redirecting to user page...\n");
        // Simulate redirection
        exit(0);
    }

    return 0;
}