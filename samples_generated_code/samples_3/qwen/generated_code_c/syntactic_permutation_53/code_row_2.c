#include <stdio.h>
#include <string.h>

int main() {
    int isLoggedIn = 1; // Change this value to simulate login status
    int isAdmin = 0;    // Change this value to simulate admin status

    if (!isLoggedIn) {
        printf("Redirecting to login page...\n");
    } else if (isAdmin) {
        printf("Redirecting to admin page...\n");
    } else {
        printf("Redirecting to user page...\n");
    }

    return 0;
}