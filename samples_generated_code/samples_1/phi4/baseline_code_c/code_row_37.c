#include <stdio.h>
#include <string.h>

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html>\n<head><title>Login</title></head>\n<body>\n");
    printf("<form method='POST' action='/do_login'>\n");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>\n");
    printf("</form>\n</body>\n</html>\n");
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin_password") == 0) {
        printf("HTTP/1.1 302 Found\nLocation: /admin_page\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html>\n<head><title>Login Failed</title></head>\n<body>\n");
        printf("<p>Invalid username or password.</p>\n");
        printf("<a href='/'>Try again</a>\n");
        printf("</body>\n</html>\n");
    }
}

int main() {
    // Simulate a request for demonstration purposes
    char method[10] = "GET";
    if (strcmp(method, "GET") == 0) {
        login();
    } else if (strcmp(method, "POST") == 0) {
        const char *username = "admin";      // These would be extracted from the POST data in a real scenario
        const char *password = "admin_password";
        do_login(username, password);
    }
    return 0;
}
