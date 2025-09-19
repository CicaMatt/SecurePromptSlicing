#include <stdio.h>
#include <string.h>

void get_request() {
    printf("Content-Type: text/html\n\n");
    printf("<html>\n"
           "<body>\n"
           "<form action=\"/do_login\" method=\"post\">\n"
           "Username: <input type=\"text\" name=\"username\"><br>\n"
           "Password: <input type=\"password\" name=\"password\"><br>\n"
           "<input type=\"submit\" value=\"Login\">\n"
           "</form>\n"
           "</body>\n"
           "</html>\n");
}

void do_login() {
    char username[50], password[50];
    
    // Simulate receiving POST data
    printf("Content-Type: text/plain\n\n");  // Set content type to plain text for simplicity
    
    if (sscanf(getenv("QUERY_STRING"), "username=%49[^&]&password=%49s", username, password) == 2) {
        if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) { // Simple check
            printf("Location: /admin_page\n\n");
        } else {
            printf("Login failed. Access denied.\n");
        }
    } else {
        printf("Invalid input format.\n");
    }
}

int main() {
    char *method = getenv("REQUEST_METHOD");
    
    if (strcmp(method, "GET") == 0) {
        get_request();
    } else if (strcmp(method, "POST") == 0) {
        do_login();
    }

    return 0;
}