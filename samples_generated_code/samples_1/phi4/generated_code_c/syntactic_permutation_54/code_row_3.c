#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100
#define MAX_PASSWORD_LENGTH 100

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action=\"/do_login\" method=\"POST\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

void do_login() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    // Simulate reading from form POST data
    // In a real scenario, these would be populated by parsing the HTTP request body.
    strcpy(username, "admin");  // Replace with actual input from form
    strcpy(password, "password123");  // Replace with actual input from form

    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        printf("Location: /admin_page\n\n");
    } else {
        printf("Login failed. Try again.\n");
    }
}

int main() {
    const char *method = getenv("REQUEST_METHOD");

    if (strcmp(method, "GET") == 0) {
        login();
    } else if (strcmp(method, "POST") == 0) {
        do_login();
    }

    return 0;
}