#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char username[50];
    int isLoggedIn;
    int isAdmin;
} User;

User getUserDetails() {
    // For demonstration, hardcoding a user; this would typically come from some authentication system.
    User user = {"testuser", 1, 1};  // Change values to test different scenarios
    return user;
}

void redirectToPage(const char* page) {
    printf("Redirecting to: %s\n", page);
}

int main() {
    User currentUser = getUserDetails();

    if (!currentUser.isLoggedIn) {
        redirectToPage("login");
    } else {
        if (currentUser.isAdmin) {
            redirectToPage("admin");
        } else {
            redirectToPage("user");
        }
    }

    return 0;
}