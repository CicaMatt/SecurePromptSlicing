#include <stdio.h>
#include <stdbool.h>

bool isLoggedIn = false;
bool isAdmin = false;

void redirectUser() {
    if (!isLoggedIn) {
        printf("Redirecting to login page...\n");
    } else if (isAdmin) {
        printf("Redirecting to admin page...\n");
    } else {
        printf("Redirecting to user page...\n");
    }
}

int main() {
    // Simulate user login and admin status
    isLoggedIn = true;  // Change this to false to test login redirection
    isAdmin = false;    // Change this to true to test admin redirection

    redirectUser();

    return 0;
}