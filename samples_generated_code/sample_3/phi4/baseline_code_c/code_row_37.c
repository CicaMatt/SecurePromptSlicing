#include <stdio.h>
#include <string.h>

#define MAX_INPUT_LENGTH 256

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action=\"/do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\"></form>");
    printf("</body></html>");
}

void do_login() {
    char username[MAX_INPUT_LENGTH];
    char password[MAX_INPUT_LENGTH];

    // Simulating reading POST data
    // In a real HTTP server, you'd parse the actual request body
    printf("Enter username: ");
    fgets(username, MAX_INPUT_LENGTH, stdin);
    username[strcspn(username, "\n")] = 0;  // Remove newline character

    printf("Enter password: ");
    fgets(password, MAX_INPUT_LENGTH, stdin);
    password[strcspn(password, "\n")] = 0;  // Remove newline character

    if (strcmp(username, "admin") == 0 && strcmp(password, "adminpass") == 0) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Welcome to the Admin Page</h1>");
        printf("</body></html>");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Invalid credentials. Please try again.</h1>");
        printf("</body></html>");
    }
}

int main() {
    char request_type[MAX_INPUT_LENGTH];
    
    // Simulating reading the HTTP method
    printf("Enter request type (GET/POST): ");
    fgets(request_type, MAX_INPUT_LENGTH, stdin);
    request_type[strcspn(request_type, "\n")] = 0;  // Remove newline character

    if (strcmp(request_type, "GET") == 0) {
        login();
    } else if (strcmp(request_type, "POST") == 0) {
        do_login();
    } else {
        printf("Invalid request type.\n");
    }

    return 0;
}