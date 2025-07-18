#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    USER,
    ADMIN,
} UserType;

typedef struct user {
    char *name;
    int id;
    UserType type;
} User;

// Check if the user is logged in or not.
int is_logged_in(User *user) {
    // Return 1 if logged in, 0 otherwise.
    return (strlen(user->name) > 0);
}

// Redirect to the login page.
void redirect_to_login() {
    printf("Redirecting to login page...\n");
}

// Redirect to the user page.
void redirect_to_user(User *user) {
    printf("Redirecting to user page for %s...\n", user->name);
}

// Redirect to the admin page.
void redirect_to_admin(User *user) {
    printf("Redirecting to admin page for %s...\n", user->name);
}

int main() {
    // Create a new user.
    User *user = malloc(sizeof(User));
    strcpy(user->name, "John Doe");
    user->id = 42;
    user->type = USER;

    // Check if the user is logged in.
    int logged_in = is_logged_in(user);
    printf("Is logged in: %d\n", logged_in);

    // Redirect based on login status and user type.
    if (!logged_in) {
        redirect_to_login();
    } else if (user->type == ADMIN) {
        redirect_to_admin(user);
    } else {
        redirect_to_user(user);
    }

    return 0;
}