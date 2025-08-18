#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        // Simulate setting the username in the session
        printf("Set session username to: %s\n", username);
        return 1; // Login successful
    }
    return 0; // Login failed
}

void show_login_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<form action=\"/login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

void show_secret_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Welcome to the Secret Settings Page</h1>");
    printf("</body></html>");
}

void show_index_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<a href=\"/login\">Secret settings</a>");
    printf("</body></html>");
}

int main() {
    char *method = getenv("REQUEST_METHOD");
    if (method && strcmp(method, "POST") == 0) {
        char username[MAX_USERNAME_LENGTH];
        char password[MAX_PASSWORD_LENGTH];
        
        // Simulate reading form data
        scanf("username=%[^&]&password=%s", username, password);
        
        if (do_login(username, password)) {
            show_secret_page();
        } else {
            printf("Content-Type: text/html\r\n\r\n");
            printf("<html><body>");
            printf("<p>Login Failed. <a href=\"/\">Try again</a></p>");
            printf("</body></html>");
        }
    } else {
        show_index_page();
    }
    
    return 0;
}