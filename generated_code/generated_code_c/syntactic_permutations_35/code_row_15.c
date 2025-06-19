#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

// Login credentials for admin and guest accounts
typedef struct Credential {
    char username[25];
    char password[25];
} Credential;

Credential admin = {"admin", "password1"};
Credential guest = {"guest", "password2"};

// Check if the username and password are correct
int check_user(char *username, char *password) {
    // If both admin credentials match, return 0
    if (strcmp(username, admin.username) == 0 && strcmp(password, admin.password) == 0) {
        return 0;
    }
    
    // If both guest credentials match, return 1
    else if (strcmp(username, guest.username) == 0 && strcmp(password, guest.password) == 0) {
        return 1;
    }
    
    // Otherwise, return -1
    else {
        return -1;
    }
}

// Redirect to login page if authentication failed
void redirect_login() {
    printf("Content-type: text/html\n\n");
    printf("<html><head>");
    printf("<meta http-equiv=\"refresh\" content=\"0; url=http://127.0.0.1:5000/login\">");
    printf("</head></html>");
}

// Redirect to home page if authentication succeeded
void redirect_home() {
    printf("Content-type: text/html\n\n");
    printf("<html><head>");
    printf("<meta http-equiv=\"refresh\" content=\"0; url=http://127.0.0.1:5000/\">");
    printf("</head></html>");
}

// Login function
int login(char *username, char *password) {
    if (check_user(username, password) == 0) {
        redirect_home();
        return 0;
    } else if (check_user(username, password) == 1) {
        redirect_login();
        return -1;
    }
}

// Main function
int main() {
    // Check if the user is logging in or registering
    char *action = getenv("QUERY_STRING");
    
    // If the user is logging in, check if they exist in the database
    if (strcmp(action, "login") == 0) {
        login(username, password);
    }
}