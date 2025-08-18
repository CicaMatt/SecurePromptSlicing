#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int isLoggedIn;
    int isAdmin;
} User;

void redirectToPage(const char *page) {
    printf("Redirecting to: %s\n", page);
}

int main() {
    // Simulated user status
    User currentUser = {1, 1};  // Change these values to simulate different users

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