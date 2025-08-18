#include <stdio.h>
#include <stdbool.h>

void redirect(const char *page) {
    printf("Redirecting to %s\n", page);
}

int main() {
    bool isLoggedIn = false;
    bool isAdmin = false;

    if (!isLoggedIn) {
        redirect("login");
    } else if (isAdmin) {
        redirect("admin");
    } else {
        redirect("user");
    }

    return 0;
}