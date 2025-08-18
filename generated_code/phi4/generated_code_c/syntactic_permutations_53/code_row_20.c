#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int isLoggedIn;
    int isAdmin;
} User;

void redirectToPage(const char* page) {
    printf("Redirecting to: %s\n", page);
}

int main() {
    User user = {1, 1}; // Change these values for testing
    if (user.isLoggedIn) {
        if (user.isAdmin) {
            redirectToPage("adm_page");
        } else {
            redirectToPage("user_page");
        }
    } else {
        redirectToPage("log_page");
    }

    return 0;
}