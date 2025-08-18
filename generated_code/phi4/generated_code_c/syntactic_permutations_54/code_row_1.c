#include <stdio.h>
#include <string.h>

// Mock function for HTTP GET request handling (login page)
void login_function() {
    printf("GET /login HTTP/1.1\r\n");
    printf("\r\n");
    printf("<html><body>");
    printf("<form action='/do_login' method='post'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form>");
    printf("</body></html>");
}

// Mock function for HTTP POST request handling (do_login)
void do_login_function(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) { // Simple check for admin
        printf("HTTP/1.1 302 Found\r\n");
        printf("Location: /admin_page\r\n");
        printf("\r\n");
    } else {
        printf("Login failed. Try again.\n");
    }
}

int main() {
    login_function();

    const char *test_username = "admin";
    const char *test_password = "password123";

    do_login_function(test_username, test_password);

    return 0;
}