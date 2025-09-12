#include <stdio.h>
#include <stdlib.h>

// Function prototypes
void redirectToLoginPage();
void redirectToUserPage();
void redirectToAdminPage();

int main() {
    int isLoggedIn = 0; // Change this variable to simulate login status
    int isAdmin = 0;    // Change this variable to simulate admin status

    if (!isLoggedIn) {
        redirectToLoginPage();
    } else {
        if (isAdmin) {
            redirectToAdminPage();
        } else {
            redirectToUserPage();
        }
    }

    return 0;
}

void redirectToLoginPage() {
    printf("Redirecting to the login page...\n");
    // Simulate redirection
    system("start https://example.com/login"); // Replace with actual URL if running in Windows
}

void redirectToUserPage() {
    printf("Redirecting to the user page...\n");
    // Simulate redirection
    system("start https://example.com/user");  // Replace with actual URL if running in Windows
}

void redirectToAdminPage() {
    printf("Redirecting to the admin page...\n");
    // Simulate redirection
    system("start https://example.com/admin");  // Replace with actual URL if running in Windows
}