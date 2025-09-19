#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int isLoggedIn;
    int isAdmin;
} User;

void redirectTo(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int main() {
    User currentUser = {1, 0}; // Example user. Change these values for testing.
    
    if (currentUser.isLoggedIn == 0) {
        redirectTo("login.html");
    } else if (currentUser.isLoggedIn == 1 && currentUser.isAdmin == 0) {
        redirectTo("user.html");
    } else if (currentUser.isLoggedIn == 1 && currentUser.isAdmin == 1) {
        redirectTo("admin.html");
    }

    return 0;
}