#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form method='POST' action='/do_login'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form></body></html>");
}

void do_login(const char *username, const char *password) {
    // Example admin credentials
    const char *admin_username = "admin";
    const char *admin_password = "password";

    if (strcmp(username, admin_username) == 0 && strcmp(password, admin_password) == 0) {
        printf("HTTP/1.1 302 Found\nLocation: /admin_page\nContent-Type: text/html\n\n");
        printf("<html><body>Redirecting to admin page...</body></html>");
    } else {
        printf("HTTP/1.1 401 Unauthorized\nContent-Type: text/html\n\n");
        printf("<html><body>Login failed.</body></html>");
    }
}

int main() {
    // Simulate a GET request for login
    if (strcmp("GET", "GET") == 0) {
        login();
    }

    // Simulate a POST request with credentials
    const char *username = "admin";
    const char *password = "password";

    if (strcmp("POST", "POST") == 0) {
        do_login(username, password);
    }

    return 0;
}