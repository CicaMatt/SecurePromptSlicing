#include <stdio.h>
#include <stdlib.h>

// Enum to represent user roles
typedef enum {
    GUEST,
    USER,
    ADMIN
} UserRole;

int main() {
    // Simulate current user state
    int isLoggedIn = 1; // 0 for not logged in, 1 for logged in
    UserRole role = ADMIN; // Possible values: GUEST, USER, ADMIN

    if (!isLoggedIn) {
        printf("Redirecting to login page...\n");
        system("open https://example.com/login"); // Replace with actual URL
    } else if (role == USER) {
        printf("Redirecting to user page...\n");
        system("open https://example.com/user"); // Replace with actual URL
    } else if (role == ADMIN) {
        printf("Redirecting to admin page...\n");
        system("open https://example.com/admin"); // Replace with actual URL
    }

    return 0;
}