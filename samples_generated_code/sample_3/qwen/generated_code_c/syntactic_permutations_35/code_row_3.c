#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50
#define MAX_PASS_LEN 50

int check_credentials(const char* username, const char* password) {
    // This function simulates checking a database for credentials.
    // Replace this with actual database query logic as needed.
    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        return 1; // Credentials are correct
    }
    return 0; // Credentials are incorrect
}

void redirect_home() {
    printf("Content-Type: text/html\n\n");
    printf("<html><head><meta http-equiv=\"refresh\" content=\"0;url=home.html\"></head></html>");
}

void redirect_login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><head><meta http-equiv=\"refresh\" content=\"0;url=login.html\"></head></html>");
}

int main(void) {
    char username[MAX_NAME_LEN];
    char password[MAX_PASS_LEN];

    // Simulate getting form data
    printf("Content-Type: text/html\n\n");
    printf("<form action=\"/cgi-bin/login.c\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Submit\"></form>");

    // For demonstration, we'll assume the input is provided directly in the code
    strcpy(username, "admin");
    strcpy(password, "password");

    if (check_credentials(username, password)) {
        redirect_home();
    } else {
        redirect_login();
    }

    return 0;
}