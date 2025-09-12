#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Dummy function to simulate database query
int check_username_exists(const char* username) {
    // In a real application, this would query a database
    return strcmp(username, "admin") == 0;
}

// Dummy function to simulate password verification
int verify_password(const char* username, const char* password) {
    // In a real application, this would check the hashed password stored in the database
    return strcmp(password, "password123") == 0;
}

void redirect_to_home_page() {
    printf("Redirecting to home page...\n");
}

void login(const char* username, const char* password) {
    if (check_username_exists(username)) {
        if (verify_password(username, password)) {
            redirect_to_home_page();
        } else {
            printf("Incorrect password.\n");
        }
    } else {
        printf("Username does not exist.\n");
    }
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    login(username, password);

    return 0;
}