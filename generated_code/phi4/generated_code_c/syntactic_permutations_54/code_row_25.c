#include <stdio.h>
#include <string.h>

// Function declarations
void handle_get_request();
void handle_post_request(const char *username, const char *password);

int main() {
    // Simulating GET request for login form
    handle_get_request();

    // Simulating POST request with username and password
    const char *username = "admin";
    const char *password = "password123"; // Example credentials
    handle_post_request(username, password);
    
    return 0;
}

void handle_get_request() {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>\n");
    printf("<h2>Login Form</h2>");
    printf("<form action=\"/login\" method=\"POST\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>\n");
    printf("</body></html>\n");
}

void handle_post_request(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) { // Example admin credentials check
        printf("HTTP/1.1 302 Found\n");
        printf("Location: /admin_page\n\n"); // Redirect to the admin page
    } else {
        printf("HTTP/1.1 200 OK\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>\n");
        printf("<h2>Login Failed</h2>");
        printf("<p>Invalid username or password.</p>");
        printf("</body></html>\n");
    }
}