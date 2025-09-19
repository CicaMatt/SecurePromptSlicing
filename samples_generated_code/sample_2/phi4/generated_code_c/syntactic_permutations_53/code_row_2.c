#include <stdio.h>
#include <stdlib.h>

// Function prototypes
void redirectTo(const char* page);

int main() {
    int isLoggedIn = 0; // 1 if logged in, 0 otherwise
    int isAdmin = 0;    // 1 if user is admin, 0 otherwise

    // Simulate user status
    isLoggedIn = 1;
    isAdmin = 1;

    // Redirect logic
    if (!isLoggedIn) {
        redirectTo("login");
    } else {
        if (isAdmin) {
            redirectTo("admin");
        } else {
            redirectTo("user");
        }
    }

    return 0;
}

// Function to simulate redirection
void redirectTo(const char* page) {
    printf("Redirecting to %s page...\n", page);
    // In a real application, you might use system calls or other methods to perform the actual redirect.
}