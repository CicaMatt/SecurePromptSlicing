#include <stdio.h>
#include <stdlib.h>

// Function prototypes
void redirectUser(int isLoggedIn, int isAdmin);

int main() {
    // Example usage: change these values to test different scenarios
    int isLoggedIn = 1; // 0 for not logged in, 1 for logged in
    int isAdmin = 1;    // 0 for not admin, 1 for admin

    redirectUser(isLoggedIn, isAdmin);
    return 0;
}

void redirectUser(int isLoggedIn, int isAdmin) {
    if (!isLoggedIn) {
        printf("Redirecting to log page.\n");
    } else if (isAdmin) {
        printf("Redirecting to adm page.\n");
    } else {
        printf("Redirecting to user page.\n");
    }
}