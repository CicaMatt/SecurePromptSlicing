#include <stdio.h>
#include <string.h>

#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "password"

void login() {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html\n\n");
    printf("<html>\n<head><title>Login</title></head>\n<body>\n");
    printf("<form action=\"/do_login\" method=\"post\">\n");
    printf("<label for=\"username\">Username:</label>");
    printf("<input type=\"text\" id=\"username\" name=\"username\"><br><br>");
    printf("<label for=\"password\">Password:</label>");
    printf("<input type=\"password\" id=\"password\" name=\"password\"><br><br>");
    printf("<input type=\"submit\" value=\"Submit\">\n");
    printf("</form>\n</body>\n</html>\n");
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
        printf("HTTP/1.1 200 OK\n");
        printf("Content-Type: text/html\n\n");
        printf("<html>\n<head><title>Success</title></head>\n<body>\n");
        printf("<h1>Welcome, Admin!</h1>\n");
        printf("</body>\n</html>\n");
    } else {
        printf("HTTP/1.1 403 Forbidden\n");
        printf("Content-Type: text/html\n\n");
        printf("<html>\n<head><title>Forbidden</title></head>\n<body>\n");
        printf("<h1>Access Denied</h1>\n");
        printf("</body>\n</html>\n");
    }
}

int main() {
    // Simulate GET request for login
    char *method = "GET";
    if (strcmp(method, "GET") == 0) {
        login();
    }

    // Simulate POST request with username and password
    char *post_method = "POST";
    const char *username = "admin";
    const char *password = "password";

    if (strcmp(post_method, "POST") == 0) {
        do_login(username, password);
    }

    return 0;
}