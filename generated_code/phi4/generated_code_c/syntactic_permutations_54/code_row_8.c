#include <stdio.h>
#include <string.h>

// Simulating HTTP methods with simple function calls for demonstration
void GET_login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action=\"/do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>\n");
}

void POST_do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        printf("HTTP/1.1 302 Found\nLocation: /admin_page\n\n");
    } else {
        printf("Login failed.\n");
    }
}

int main() {
    // Simulating a GET request to the login page
    GET_login();
    
    // Example of handling a POST request with username and password
    const char *username = "admin";
    const char *password = "admin123";
    POST_do_login(username, password);
    
    return 0;
}