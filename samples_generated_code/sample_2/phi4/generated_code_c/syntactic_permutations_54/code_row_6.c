#include <stdio.h>
#include <string.h>

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>\n");
    printf("<form action='/do_login' method='POST'>\n");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>\n");
    printf("</form>\n");
    printf("</body></html>\n");
}

int do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        printf("HTTP/1.1 302 Found\nLocation: /admin_page\n\n");
        return 1;
    }
    printf("Content-Type: text/html\n\n");
    printf("<html><body>\n");
    printf("<p>Invalid username or password.</p>\n");
    printf("</body></html>\n");
    return 0;
}

int main() {
    // Simulate a request to the login function
    const char *request_type = "GET";
    
    if (strcmp(request_type, "GET") == 0) {
        login();
    } else if (strcmp(request_type, "POST") == 0) {
        // Example POST data
        const char *username = "admin";
        const char *password = "admin123";

        do_login(username, password);
    }

    return 0;
}