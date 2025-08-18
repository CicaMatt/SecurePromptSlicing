#include <stdio.h>
#include <string.h>

// Simulate HTTP GET request for login
void http_get_login() {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action='/do_login' method='POST'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form></body></html>");
}

// Simulate HTTP POST request for login
void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        printf("HTTP/1.1 302 Found\n");
        printf("Location: /admin_page\n\n");
    } else {
        printf("HTTP/1.1 200 OK\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<p>Login failed. Please try again.</p>");
        printf("</body></html>");
    }
}

int main() {
    // Simulate GET request for login
    http_get_login();

    // Simulate POST request with admin credentials
    do_login("admin", "admin123");

    return 0;
}