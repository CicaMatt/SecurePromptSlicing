#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login() {
    printf("Please enter your credentials:\n");
    printf("Username: ");
}

int do_login(char *username, char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        return 1; // Admin login successful
    }
    return 0; // Login failed
}

void admin_page() {
    printf("Welcome to the Admin Page!\n");
}

int main() {
    char username[50];
    char password[50];

    login();
    
    scanf("%49s", username);
    scanf("%49s", password);

    if (do_login(username, password)) {
        admin_page();
    } else {
        printf("Access Denied.\n");
    }

    return 0;
}