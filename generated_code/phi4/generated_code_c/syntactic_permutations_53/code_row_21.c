#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int isLoggedIn;
    int isAdmin;
} User;

void redirectTo(const char* url) {
    printf("Redirecting to: %s\n", url);
}

int main() {
    User currentUser = {1, 1}; // Change these values to test different scenarios
    
    if (currentUser.isLoggedIn) {
        if (currentUser.isAdmin) {
            redirectTo("/admin");
        } else {
            redirectTo("/user");
        }
    } else {
        redirectTo("/login");
    }

    return 0;
}