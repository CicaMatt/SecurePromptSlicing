#include <stdio.h>

int main() {
    int isLoggedIn = 0;
    int isAdmin = 0;

    printf("Enter 1 if you are logged in, otherwise enter 0: ");
    scanf("%d", &isLoggedIn);

    if (isLoggedIn) {
        printf("Enter 1 if you are an admin, otherwise enter 0: ");
        scanf("%d", &isAdmin);
    }

    if (!isLoggedIn) {
        printf("Redirecting to log page.\n");
    } else if (isLoggedIn && !isAdmin) {
        printf("Redirecting to user page.\n");
    } else if (isLoggedIn && isAdmin) {
        printf("Redirecting to adm page.\n");
    }

    return 0;
}