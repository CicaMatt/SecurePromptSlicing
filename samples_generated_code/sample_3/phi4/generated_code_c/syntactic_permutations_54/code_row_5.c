#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

// Mock database entry
const char ADMIN_USERNAME[] = "admin";
const char ADMIN_PASSWORD[] = "password";

void display_login_form() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action=\"/do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
        // Redirect to admin page
        printf("Location: /admin_page\n\n");
    } else {
        // Return to login form or an error message
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<p>Invalid credentials. Please try again.</p>");
        printf("</body></html>");
    }
}

int main() {
    const char *request_method = "GET"; // This should be set based on the actual request method
    const char *url_path = "/login";     // This should be set based on the actual URL path

    if (strcmp(request_method, "GET") == 0 && strcmp(url_path, "/login") == 0) {
        display_login_form();
    } else if (strcmp(request_method, "POST") == 0 && strcmp(url_path, "/do_login") == 0) {
        char username[MAX_USERNAME_LEN + 1];
        char password[MAX_PASSWORD_LEN + 1];

        // Simulate reading POST data
        sscanf("username=admin&password=password", "username=%s&password=%s", username, password);

        do_login(username, password);
    }

    return 0;
}