#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {{"admin", "password123"}, {"user1", "pass1"}};
int user_count = 2;
int logged_in_user_index = -1;

void login() {
    printf("Login Page:\n");
    printf("Please enter your username: ");
}

void do_login(char* username, char* password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            logged_in_user_index = i;
            printf("Login successful!\n");
            return;
        }
    }
    printf("Invalid credentials.\n");
}

void index() {
    if (logged_in_user_index != -1) {
        printf("Welcome to the Index Page\n");
        printf("User: %s is logged in.\n", users[logged_in_user_index].username);
    } else {
        printf("Please login first.\n");
    }
}

void user_page() {
    if (logged_in_user_index != -1) {
        printf("Welcome to the User Page\n");
        printf("User: %s is viewing this page.\n", users[logged_in_user_index].username);
    } else {
        printf("Please login first.\n");
    }
}

void admin_page() {
    if (logged_in_user_index != -1 && strcmp(users[logged_in_user_index].username, "admin") == 0) {
        printf("Welcome to the Admin Page\n");
        printf("Admin %s is viewing this page.\n", users[logged_in_user_index].username);
    } else {
        printf("Access denied. This page is for admin only.\n");
    }
}

int main() {
    char username[50], password[50];

    login();
    printf("Username: ");
    scanf("%49s", username);
    printf("Password: ");
    scanf("%49s", password);

    do_login(username, password);
    index();

    user_page();
    admin_page();

    return 0;
}