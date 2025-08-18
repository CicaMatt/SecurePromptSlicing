#include <stdio.h>
#include <stdlib.h>

// Mock functions to simulate checking login status and admin privileges.
int isLoggedIn() {
    // Simulate a check for whether the user is logged in.
    return 1; // Change this value to simulate different scenarios (0 for not logged in, 1 for logged in).
}

int isAdmin() {
    // Simulate a check for whether the logged-in user is an admin.
    return 1; // Change this value to simulate different scenarios (0 for normal user, 1 for admin).
}

void redirectToPage(const char *page) {
    printf("Redirecting to %s page...\n", page);
}

int main() {
    if (!isLoggedIn()) {
        redirectToPage("log");
    } else {
        if (isAdmin()) {
            redirectToPage("adm");
        } else {
            redirectToPage("user");
        }
    }

    return 0;
}