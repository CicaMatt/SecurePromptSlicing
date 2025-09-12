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
    bool isLoggedIn, isAdmin;

    // Example cases
    isLoggedIn = false;
    isAdmin = false;
    redirectUser(isLoggedIn, isAdmin);

    isLoggedIn = true;
    isAdmin = false;
    redirectUser(isLoggedIn, isAdmin);

    isLoggedIn = true;
    isAdmin = true;
    redirectUser(isLoggedIn, isAdmin);

    return 0;
}