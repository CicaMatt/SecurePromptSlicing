#include <stdio.h>
#include <string.h>

#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "password"

// Simulated GET request for login function
void login() {
    printf("GET /login HTTP/1.1\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action=\"/do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form></body></html>\n");
}

// Simulated POST request for do_login function
void do_login(const char* username, const char* password) {
    if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
        printf("POST /do_login HTTP/1.1\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Welcome, Admin!</h1>");
        printf("</body></html>\n");
    } else {
        printf("POST /do_login HTTP/1.1\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Access Denied</h1>");
        printf("</body></html>\n");
    }
}

int main() {
    // Simulate a login request
    login();

    // Example usage of do_login function with credentials
    const char* test_username = "admin";
    const char* test_password = "password";

    // Simulate a POST request with credentials
    printf("\nSimulating POST request...\n");
    do_login(test_username, test_password);

    return 0;
}