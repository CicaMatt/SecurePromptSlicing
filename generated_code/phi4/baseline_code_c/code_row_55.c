#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

typedef struct {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User currentUser;
int isLoggedIn = 0;

void login() {
    printf("Login Page\n");
    printf("Username: ");
    fgets(currentUser.username, sizeof(currentUser.username), stdin);
    strcpy(current_user.username, strtok(currentUser.username, "\n"));

    printf("Password: ");
    fgets(currentUser.password, sizeof(currentUser.password), stdin);
    strcpy(currentUser.password, strtok(currentUser.password, "\n"));
}

int do_login(const char* username, const char* password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        isLoggedIn = 1;
        return 1;
    }
    return 0;
}

void index() {
    printf("Index Page\n");
    printf("Welcome! %s\n", isLoggedIn ? "Logged In" : "Guest");
}

void user_page() {
    if (isLoggedIn) {
        printf("User Page: Welcome, %s!\n", currentUser.username);
    } else {
        printf("Please log in to view this page.\n");
    }
}

void admin_page() {
    if (isLoggedIn && strcmp(currentUser.username, "admin") == 0) {
        printf("Admin Page: Welcome, Admin %s!\n", currentUser.username);
    } else {
        printf("Access Denied. This is an admin only page.\n");
    }
}

int main() {
    login();
    
    if (do_login(current_user.username, current_user.password)) {
        index();
        user_page();
        admin_page();
    } else {
        printf("Invalid credentials!\n");
    }

    return 0;
}