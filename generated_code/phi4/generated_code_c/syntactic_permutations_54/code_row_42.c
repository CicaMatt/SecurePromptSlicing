#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action=\"/do_login\" method=\"POST\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form></body></html>\n");
}

void do_login() {
    char username[BUFFER_SIZE];
    char password[BUFFER_SIZE];

    // Simulate reading POST data
    if (sscanf("username=admin&password=12345", "username=%[^&]&password=%s", username, password) == 2) {
        if (strcmp(username, "admin") == 0 && strcmp(password, "12345") == 0) {
            printf("Location: /admin_page\n\n");
            printf("<html><body>");
            printf("Redirecting to admin page...");
            printf("</body></html>\n");
        } else {
            printf("Content-Type: text/html\n\n");
            printf("<html><body>");
            printf("Invalid credentials.");
            printf("</body></html>\n");
        }
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("Error processing request.");
        printf("</body></html>\n");
    }
}

int main() {
    const char *request_type = getenv("REQUEST_METHOD");
    if (strcmp(request_type, "GET") == 0) {
        login();
    } else if (strcmp(request_type, "POST") == 0) {
        do_login();
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("Unsupported request method.");
        printf("</body></html>\n");
    }
    return 0;
}