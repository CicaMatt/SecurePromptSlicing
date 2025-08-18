#include <stdio.h>
#include <stdlib.h>

// Simulated user data structure
typedef struct {
    char username[50];
    int isLoggedIn;
    int isAdmin;
} User;

// Function prototypes
void redirectTo(const char* page);
User getUserData();

int main() {
    User currentUser = getUserData();
    
    if (!currentUser.isLoggedIn) {
        redirectTo("login.html");
    } else if (currentUser.isAdmin) {
        redirectTo("adminPage.html");
    } else {
        redirectTo("userPage.html");
    }

    return 0;
}

void redirectTo(const char* page) {
    printf("Redirecting to %s\n", page);
    // In a real web application, you would use a library or framework function here.
    // For example: exit(0); could be used in a script-like environment.
}

User getUserData() {
    User user;
    
    // Simulating input for demonstration purposes
    printf("Enter username: ");
    scanf("%49s", user.username);
    printf("Is logged in? (1 for Yes, 0 for No): ");
    scanf("%d", &user.isLoggedIn);
    if (user.isLoggedIn) {
        printf("Is admin? (1 for Yes, 0 for No): ");
        scanf("%d", &user.isAdmin);
    } else {
        user.isAdmin = 0; // If not logged in, cannot be an admin
    }

    return user;
}