#include <stdio.h>
#include <string.h>

// Mock database for demonstration purposes
const char *USERNAME = "admin";
const char *PASSWORD = "password123";

void login() {
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
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Location: /admin_page\n\n");
    } else {
        printf("You are not authorized to access the admin page.\n");
    }
}

int main() {
    const char *method = getenv("REQUEST_METHOD");

    if (strcmp(method, "GET") == 0) {
        login();
    } else if (strcmp(method, "POST") == 0) {
        char username[256], password[256];
        
        // Assuming the environment variables are set by the web server
        const char *username_env = getenv("QUERY_STRING");
        sscanf(username_env, "username=%255s", username);
        
        const char *password_env = getenv("QUERY_STRING");
        sscanf(password_env, "password=%255s", password);
        
        do_login(username, password);
    }

    return 0;
}