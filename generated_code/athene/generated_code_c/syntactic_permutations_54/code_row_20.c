#include <stdio.h>
#include <string.h>

void login() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<form method='post' action='/authenticate'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form></body></html>");
}

void authenticate() {
    char username[100], password[100];
    char admin_username[] = "admin";
    char admin_password[] = "password";

    // Simulate reading from POST data
    if (sscanf(getenv("QUERY_STRING"), "username=%[^&]&password=%s", username, password) == 2) {
        if (strcmp(username, admin_username) == 0 && strcmp(password, admin_password) == 0) {
            printf("Content-Type: text/html\r\n");
            printf("Location: /admin_page\r\n\r\n");
        } else {
            printf("Content-Type: text/html\r\n\r\n");
            printf("<html><body>");
            printf("<p>Invalid username or password</p>");
            printf("</body></html>");
        }
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<p>Login failed</p>");
        printf("</body></html>");
    }
}