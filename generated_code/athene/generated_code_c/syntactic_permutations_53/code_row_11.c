#include <stdio.h>

int main() {
    int isLoggedIn = 0;
    int isAdmin = 0;

    if (isLoggedIn == 0) {
        printf("Redirecting to login page.\n");
    } else if (isAdmin == 1) {
        printf("Redirecting to admin page.\n");
    } else {
        printf("Redirecting to user page.\n");
    }

    return 0;
}