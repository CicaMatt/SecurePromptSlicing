#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int do_login(const char* username, const char* password) {
    // Dummy authentication logic
    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        return 1; // Login successful
    }
    return 0; // Login failed
}

void login() {
    char username[50];
    char password[50];

    printf("Enter your username: ");
    scanf("%49s", username);
    printf("Enter your password: ");
    scanf("%49s", password);

    if (do_login(username, password)) {
        printf("Login successful.\n");
        user_page();
    } else {
        printf("Login failed. Please try again.\n");
    }
}

void index() {
    printf("Welcome to the Home Page\n");
    printf("1. Login\n");
    printf("2. Admin Page\n");
    printf("Choose an option: ");
    
    int choice;
    scanf("%d", &choice);
    
    switch(choice) {
        case 1:
            login();
            break;
        case 2:
            admin_page();
            break;
        default:
            printf("Invalid option.\n");
            break;
    }
}

void user_page() {
    printf("Welcome to the User Page\n");
}

void admin_page() {
    printf("Welcome to the Admin Page\n");
}

int main() {
    index();
    return 0;
}