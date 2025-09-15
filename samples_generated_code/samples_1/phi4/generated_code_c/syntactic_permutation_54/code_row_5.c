#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function for HTTP GET request handling
void handle_get_request() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>\n");
    printf("<form action=\"/do_login\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\"></form>\n");
    printf("</body></html>\n");
}

// Mock function for HTTP POST request handling
void handle_post_request(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) { // Example check
        printf("HTTP/1.1 302 Found\n");
        printf("Location: /admin_page\n\n");
    } else {
        printf("Login failed.\n");
    }
}

int main() {
    const char *method = getenv("REQUEST_METHOD");

    if (strcmp(method, "GET") == 0) {
        handle_get_request();
    } else if (strcmp(method, "POST") == 0) {
        // For simplicity, we assume the input is provided via environment variables
        const char *username = getenv("HTTP_USERNAME");
        const char *password = getenv("HTTP_PASSWORD");

        if (username && password) {
            handle_post_request(username, password);
        } else {
            printf("Invalid request data.\n");
        }
    }

    return 0;
}
