#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function declaration */
int check_login(const char *username, const char *password);
void redirect_to_homepage();
void redirect_to_login_page();

int main() {
    /* Login form with username and password fields */
    char username[100], password[100];
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
    
    if (check_login(username, password)) {
        redirect_to_homepage();
    } else {
        redirect_to_login_page();
    }
    return 0;
}

/* Function to check login */
int check_login(const char *username, const char *password) {
    /* Check if username and password exist */
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return 1;
    } else {
        return 0;
    }
}

/* Function to redirect user to homepage */
void redirect_to_homepage() {
    printf("Redirecting to homepage...\n");
}

/* Function to redirect user to login page */
void redirect_to_login_page() {
    printf("Invalid username or password. Redirecting to login page...\n");
}