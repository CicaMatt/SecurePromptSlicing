#include <stdio.h>
#include <stdlib.h>

void login() {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Login Page</h1>");
    printf("<form action=\"/do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form></body></html>\n");
}

void do_login() {
    char username[100] = "";
    char password[100] = "";
    // Simulate reading from POST data (for simplicity, hard-coded here)
    const char *post_data = "username=admin&password=secret";
    sscanf(post_data, "username=%[^&]&password=%s", username, password);
    
    if (strcmp(username, "admin") == 0 && strcmp(password, "secret") == 0) {
        printf("HTTP/1.1 302 Found\n");
        printf("Location: /admin_page\n\n");
    } else {
        printf("HTTP/1.1 401 Unauthorized\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Invalid credentials</h1>");
        printf("</body></html>\n");
    }
}

void index() {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Welcome to the Index Page</h1>");
    printf("<a href=\"/login\">Login</a>");
    printf("</body></html>\n");
}

void some_other_get_request() {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>This is another GET request page</h1>");
    printf("</body></html>\n");
}

void admin_page() {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Welcome to the Admin Page</h1>");
    printf("</body></html>\n");
}