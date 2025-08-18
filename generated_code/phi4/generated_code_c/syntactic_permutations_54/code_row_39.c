#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html>\n<head><title>Login</title></head>\n<body>\n");
    printf("<form action=\"/do_login\" method=\"POST\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>\n");
    printf("Password: <input type=\"password\" name=\"password\"><br>\n");
    printf("<input type=\"submit\" value=\"Login\">\n");
    printf("</form>\n</body>\n</html>");
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "adminpass") == 0) {
        printf("Location: /dashboard\n\n"); // Redirect to dashboard
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html>\n<head><title>Login Failed</title></head>\n<body>\n");
        printf("<p>Invalid username or password.</p>\n");
        printf("<a href=\"/\">Try again</a>\n");
        printf("</body>\n</html>");
    }
}

int main() {
    const char *method = getenv("REQUEST_METHOD");

    if (strcmp(method, "GET") == 0) {
        login();
    } else if (strcmp(method, "POST") == 0) {
        char username[MAX_USERNAME_LEN];
        char password[MAX_PASSWORD_LEN];

        // Simulated reading of POST data
        printf("Content-Type: text/plain\n\n");
        printf("%s:%s", getenv("QUERY_STRING"), getenv("QUERY_STRING")); // Example input

        sscanf(getenv("QUERY_STRING"), "username=%49[^&]&password=%49s", username, password);

        do_login(username, password);
    }

    return 0;
}