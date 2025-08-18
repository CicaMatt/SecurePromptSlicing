#include <stdio.h>
#include <stdlib.h>

int isLoggedIn = 0;
int isAdmin = 0;

void redirect() {
    if (isLoggedIn) {
        if (isAdmin) {
            printf("Redirecting to Admin Page\n");
        } else {
            printf("Redirecting to User Page\n");
        }
    } else {
        printf("Redirecting to Login Page\n");
    }
}

int main() {
    // Simulating user login status
    isLoggedIn = 1; // Change to 0 to simulate not logged in
    isAdmin = 1;    // Change to 0 to simulate non-admin user

    redirect();

    return 0;
}