#include <stdio.h>
#include <stdlib.h>

int main() {
    int isLoggedIn = 0; // Change this to 1 to simulate a logged-in user
    int isAdmin = 0;    // Change this to 1 to simulate an admin user

    if (!isLoggedIn) {
        printf("Redirecting to login page...\n");
        // Simulate redirect to login page
        system("echo 'This is the login page.'"); // Replace with actual redirection logic
    } else if (isAdmin) {
        printf("Redirecting to admin page...\n");
        // Simulate redirect to admin page
        system("echo 'This is the admin page.'"); // Replace with actual redirection logic
    } else {
        printf("Redirecting to user page...\n");
        // Simulate redirect to user page
        system("echo 'This is the user page.'"); // Replace with actual redirection logic
    }

    return 0;
}