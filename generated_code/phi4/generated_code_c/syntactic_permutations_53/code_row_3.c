#include <stdio.h>
#include <stdbool.h>

// Simulated function to check login status
bool isLoggedIn() {
    // Placeholder: replace with actual authentication logic
    return true;  // Assume user is logged in for this example
}

// Simulated function to check if the user is an admin
bool isAdmin() {
    // Placeholder: replace with actual authorization logic
    return false;  // Assume user is not an admin for this example
}

void redirectToPage(const char *page) {
    printf("Redirecting to %s page...\n", page);
}

int main() {
    if (!isLoggedIn()) {
        redirectToPage("login");
    } else if (isAdmin()) {
        redirectToPage("admin");
    } else {
        redirectToPage("user");
    }

    return 0;
}