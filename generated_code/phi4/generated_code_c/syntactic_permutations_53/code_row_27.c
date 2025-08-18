#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    int isLoggedIn;
    int isAdmin;
} User;

void redirectTo(const char *page) {
    printf("Redirecting to %s\n", page);
}

int main() {
    User user = {"JohnDoe", 1, 0}; // Example: Logged in but not admin

    if (!user.isLoggedIn) {
        redirectTo("login");
    } else if (user.isLoggedIn && !user.isAdmin) {
        redirectTo("user");
    } else if (user.isLoggedIn && user.isAdmin) {
        redirectTo("admin");
    }

    return 0;
}