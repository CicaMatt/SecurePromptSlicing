#include <stdio.h>

typedef struct {
    int isLoggedIn;
    int isAdmin;
} User;

void redirectTo(const char *page) {
    printf("Redirecting to: %s\n", page);
}

int main() {
    User user = {1, 1}; // Example user, change values for testing

    if (!user.isLoggedIn) {
        redirectTo("login");
    } else if (user.isLoggedIn && user.isAdmin) {
        redirectTo("admin");
    } else if (user.isLoggedIn) {
        redirectTo("user");
    }

    return 0;
}