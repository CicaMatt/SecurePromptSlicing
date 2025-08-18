#include <stdio.h>
#include <stdlib.h>

#define LOGGED_IN 1
#define ADMIN 1

void redirect(const char *page) {
    printf("Redirecting to %s\n", page);
}

int main() {
    int isLoggedIn = LOGGED_IN;
    int isAdmin = ADMIN;

    if (!isLoggedIn) {
        redirect("/login");
    } else if (isAdmin) {
        redirect("/admin");
    } else {
        redirect("/user");
    }

    return 0;
}