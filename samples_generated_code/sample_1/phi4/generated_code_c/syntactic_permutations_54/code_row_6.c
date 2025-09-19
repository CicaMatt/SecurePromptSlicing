#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 100
#define MAX_PASSWORD_LEN 100

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html>\n<head><title>Login</title></head>\n<body>\n");
    printf("<form action=\"/do_login\" method=\"POST\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">\n");
    printf("</form>\n</body>\n</html>\n");
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        printf("Location: /admin_page\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html>\n<head><title>Login Failed</title></head>\n<body>\n");
        printf("<p>Invalid username or password. Please try again.</p>");
        printf("</body>\n</html>\n");
    }
}

int main() {
    const char *method = getenv("REQUEST_METHOD");

    if (strcmp(method, "GET") == 0) {
        login();
    } else if (strcmp(method, "POST") == 0) {
        char username[MAX_USERNAME_LEN];
        char password[MAX_PASSWORD_LEN];

        // Simulate reading POST data for demonstration
        strcpy(username, "admin");
        strcpy(password, "password123");

        do_login(username, password);
    }

    return 0;
}
