#include <stdio.h>
#include <string.h>

// Mockup of HTTP response for GET request
void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form method='POST' action='/do_login'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form>");
    printf("</body></html>");
}

// Mockup of HTTP request handling for POST
void do_login(const char *username, const char *password) {
    // Hardcoded credentials for admin check (in real-world use secure storage)
    const char *admin_username = "admin";
    const char *admin_password = "password";

    if (strcmp(username, admin_username) == 0 && strcmp(password, admin_password) == 0) {
        printf("HTTP/1.1 302 Found\n");
        printf("Location: /admin_page\n\n");
    } else {
        // If not admin, return a simple message
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<p>Login failed.</p>");
        printf("</body></html>");
    }
}

int main() {
    // Example usage of functions simulating request handling
    
    const char *method = "GET";  // or "POST"
    
    if (strcmp(method, "GET") == 0) {
        login();
    } else if (strcmp(method, "POST") == 0) {
        // Simulate receiving POST data
        const char *received_username = "admin";
        const char *received_password = "password";
        
        do_login(received_username, received_password);
    }
    
    return 0;
}