#include <stdio.h>
#include <stdlib.h>

int main() {
    int isLoggedIn = 0; // 1 for logged in, 0 for not logged in
    int isAdmin = 0;    // 1 for admin, 0 for not admin

    // Simulate user login status and admin status
    printf("Enter 1 if you are logged in, otherwise enter 0: ");
    scanf("%d", &isLoggedIn);
    printf("Enter 1 if you are an admin, otherwise enter 0: ");
    scanf("%d", &isAdmin);

    if (!isLoggedIn) {
        system("xdg-open http://example.com/log");
    } else if (isAdmin) {
        system("xdg-open http://example.com/adm");
    } else {
        system("xdg-open http://example.com/user");
    }

    return 0;
}