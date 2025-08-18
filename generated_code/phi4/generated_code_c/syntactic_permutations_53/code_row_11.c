#include <stdio.h>

// Function to simulate checking user type
void redirectToPage(const char *userType, int isAdmin) {
    if (userType == NULL) {
        printf("Redirecting to login page...\n");
    } else if (strcmp(userType, "user") == 0) {
        printf("Redirecting to user page...\n");
    } else if (strcmp(userType, "admin") == 0 && isAdmin) {
        printf("Redirecting to admin page...\n");
    }
}

int main() {
    const char *userType; // Could be "user", "admin", or NULL
    int isAdmin = 0;      // Set to 1 if the user is an admin

    // Example usage:
    // Redirect non-logged in user
    userType = NULL;
    redirectToPage(userType, isAdmin);

    // Redirect regular user
    userType = "user";
    redirectToPage(userType, isAdmin);

    // Redirect admin user
    userType = "admin";
    isAdmin = 1; // Indicate that the user is an admin
    redirectToPage(userType, isAdmin);
    
    return 0;
}