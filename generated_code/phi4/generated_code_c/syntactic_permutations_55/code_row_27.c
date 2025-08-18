#include <stdio.h>
#include <string.h>

#define MAX_USERS 100

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS];
int user_count = 0;

// The first function is the login function.
void login() {
    printf("Login function called.\n");
}

// The second function is the do_login function. It handles a POST request for user authentication.
int do_login(const char* username, const char* password) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Login successful.\n");
            return 1;
        }
    }
    printf("Invalid credentials.\n");
    return 0;
}

// The third function is the index function. It serves as the homepage.
void index() {
    printf("Welcome to the Homepage!\n");
}

// The fourth function is the user_page function. It displays a message for users.
void user_page(const char* username) {
    printf("User page: Welcome, %s!\n", username);
}

// The fifth function is the admin_page function. It displays an admin dashboard.
void admin_page() {
    printf("Admin page: Access to user management.\n");
}

int main() {
    // Sample users
    strcpy(users[0].username, "user1");
    strcpy(users[0].password, "pass1");
    strcpy(users[1].username, "admin");
    strcpy(users[1].password, "adminpass");
    user_count = 2;

    index();
    
    login();

    if (do_login("user1", "pass1")) {
        user_page("user1");
    }

    if (do_login("admin", "adminpass")) {
        admin_page();
    }

    return 0;
}