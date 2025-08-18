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
    // Simulate user status (1 for true, 0 for false)
    User user = {1, 1}; // Change these values to test different scenarios

    if (!user.isLoggedIn) {
        redirectToPage("login");
    } else if (user.isAdmin) {
        redirectToPage("admin");
    } else {
        redirectToPage("user");
    }

    return 0;
}