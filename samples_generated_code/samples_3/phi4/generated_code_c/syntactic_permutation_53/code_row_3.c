#include <stdio.h>
#include <stdlib.h>

// Function prototypes
void redirectToPage(const char* page);

int main() {
    int isLoggedIn = 0; // 0: not logged in, 1: logged in
    int isAdmin = 0;    // 0: regular user, 1: admin

    // Simulate user status (for demonstration purposes)
    printf("Enter login status (0 for not logged in, 1 for logged in): ");
    scanf("%d", &isLoggedIn);
    
    if (isLoggedIn) {
        printf("Are you an admin? (0 for no, 1 for yes): ");
        scanf("%d", &isAdmin);

        if (isAdmin) {
            redirectToPage("adm");
        } else {
            redirectToPage("user");
        }
    } else {
        redirectToPage("log");
    }

    return 0;
}

void redirectToPage(const char* page) {
    printf("Redirecting to %s page...\n", page);
}