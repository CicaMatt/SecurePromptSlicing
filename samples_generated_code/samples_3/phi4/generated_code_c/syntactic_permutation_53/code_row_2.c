#include <stdio.h>
#include <string.h>

void redirectUser(const char* userType, int isAdmin) {
    if (strcmp(userType, "login") == 0) {
        printf("Redirecting to login page...\n");
    } else if (strcmp(userType, "user") == 0 && !isAdmin) {
        printf("Redirecting to user page...\n");
    } else if (strcmp(userType, "admin") == 0 && isAdmin) {
        printf("Redirecting to admin page...\n");
    }
}

int main() {
    const char* userType = "user"; // Options: "login", "user", "admin"
    int isAdmin = 1; // 1 if the user is an admin, 0 otherwise

    redirectUser(userType, isAdmin);

    return 0;
}