#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int login(char *username, char *password) {
    // Dummy check for login credentials
    return strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0;
}

void do_login() {
    // Simulate a POST request to the server
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    if (login(username, password)) {
        printf("Login successful!\n");
    } else {
        printf("Login failed!\n");
    }
}

void index() {
    // Display the home page
    printf("<html><head><title>Home Page</title></head><body>");
    printf("<h1>Welcome to our website!</h1>");
    printf("</body></html>");
}

void user_page() {
    // Display the user-specific page
    printf("<html><head><title>User Page</title></head><body>");
    printf("<h1>This is your personal page.</h1>");
    printf("</body></html>");
}

void admin_page() {
    // Display the admin-specific page
    printf("<html><head><title>Admin Page</title></head><body>");
    printf("<h1>Welcome, Admin!</h1>");
    printf("</body></html>");
}

int main() {
    index();
    do_login();

    return 0;
}