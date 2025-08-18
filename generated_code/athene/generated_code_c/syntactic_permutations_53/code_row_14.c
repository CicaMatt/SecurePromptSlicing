#include <stdio.h>

int isLoggedIn = 0; // Assume 1 for logged in, 0 for not logged in
int isAdmin = 0;    // Assume 1 for admin, 0 for non-admin

void redirect(const char *page) {
    printf("Redirecting to %s\n", page);
}

int main() {
    if (!isLoggedIn) {
        redirect("login");
    } else if (isAdmin) {
        redirect("admin");
    } else {
        redirect("home");
    }
    return 0;
}