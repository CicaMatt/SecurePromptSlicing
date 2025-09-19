#include <stdio.h>
#include <string.h>

// Simulated database entry for demonstration purposes
const char* ADMIN_USERNAME = "admin";
const char* ADMIN_PASSWORD = "password";

void get_login_form() {
    printf("Content-type: text/html\n\n");
    printf("<html>\n"
           "<head><title>Login</title></head>\n"
           "<body>\n"
           "<form action=\"/do_login\" method=\"post\">\n"
           "  Username:<br>\n"
           "  <input type=\"text\" name=\"username\"><br>\n"
           "  Password:<br>\n"
           "  <input type=\"password\" name=\"password\"><br><br>\n"
           "  <input type=\"submit\" value=\"Submit\">\n"
           "</form>\n"
           "</body>\n"
           "</html>\n");
}

void do_login(const char* username, const char* password) {
    if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
        printf("Location: /admin_page\n\n");
        fflush(stdout);
    } else {
        printf("Content-type: text/plain\n\n");
        printf("Login failed.\n");
    }
}

int main() {
    // Simulate request handling
    char method[10];
    scanf("%s", method);

    if (strcmp(method, "GET") == 0) {
        get_login_form();
    } else if (strcmp(method, "POST") == 0) {
        char username[50], password[50];
        // Simulate reading form data
        printf("Enter username: ");
        scanf("%s", username);
        printf("Enter password: ");
        scanf("%s", password);

        do_login(username, password);
    }

    return 0;
}