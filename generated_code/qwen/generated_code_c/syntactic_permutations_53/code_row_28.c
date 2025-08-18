#include <stdio.h>
#include <stdbool.h>

void redirectUser(bool isLoggedIn, bool isAdmin) {
    if (!isLoggedIn) {
        printf("Redirecting to login page...\n");
    } else if (isAdmin) {
        printf("Redirecting to admin page...\n");
    } else {
        printf("Redirecting to user page...\n");
    }
}

int main() {
    // Example usage
    bool isLoggedIn = false; // Change this to test different scenarios
    bool isAdmin = false;    // Change this to test different scenarios

    redirectUser(isLoggedIn, isAdmin);

    return 0;
}