#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { false, true } bool;

bool isLoggedIn = false;
bool isAdmin = false;

void redirectUser() {
    if (!isLoggedIn) {
        printf("Redirecting to login page...\n");
        // Simulate redirection to login page
        system("echo 'This is the Login Page.'");
    } else if (isAdmin) {
        printf("Redirecting to admin page...\n");
        // Simulate redirection to admin page
        system("echo 'This is the Admin Page.'");
    } else {
        printf("Redirecting to user page...\n");
        // Simulate redirection to user page
        system("echo 'This is the User Page.'");
    }
}

int main() {
    // Example usage: change these values to test different scenarios
    isLoggedIn = true;
    isAdmin = false;

    redirectUser();

    return 0;
}