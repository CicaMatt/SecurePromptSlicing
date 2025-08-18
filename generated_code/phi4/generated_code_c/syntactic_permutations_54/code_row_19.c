#include <stdio.h>
#include <string.h>

// Simulating HTTP GET method for login page.
void http_get_login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action=\"/login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

// Simulating HTTP POST method for login authentication.
void http_post_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        printf("HTTP/1.1 302 Found\n");
        printf("Location: /admin_page\n\n");
    } else {
        printf("Login failed. Please try again.\n");
    }
}

int main() {
    const char *method = "GET"; // Change to "POST" to simulate a POST request.

    if (strcmp(method, "GET") == 0) {
        http_get_login();
    } else if (strcmp(method, "POST") == 0) {
        // Example credentials; in practice, get these from the HTTP POST body.
        const char *username = "admin";
        const char *password = "admin123";
        http_post_login(username, password);
    }

    return 0;
}