#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void redirectTo(const char *url) {
    printf("Location: %s\n", url);
}

void handleRequest(const char *path, const char *method, const char *username = NULL, const char *password = NULL) {
    if (strcmp(path, "/") == 0 && strcmp(method, "GET") == 0) {
        printf("<html><body>\n");
        printf("<h1>Welcome to the Index Page</h1>\n");
        printf("<a href=\"/login\">Login</a>\n");
        printf("</body></html>");
    } else if (strcmp(path, "/login") == 0) {
        if (strcmp(method, "GET") == 0) {
            printf("<html><body>\n");
            printf("<h1>Login Page</h1>\n");
            printf("<form action=\"/login\" method=\"post\">\n");
            printf("Username: <input type=\"text\" name=\"username\"><br>");
            printf("Password: <input type=\"password\" name=\"password\"><br>");
            printf("<input type=\"submit\" value=\"Login\">\n");
            printf("</form>\n");
            printf("</body></html>");
        } else if (strcmp(method, "POST") == 0) {
            // Hardcoded credentials for demonstration
            if (username != NULL && password != NULL &&
                strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {

                // Set session variable (simulated here)
                printf("Set-Cookie: username=admin\n");
                redirectTo("/secret");
            } else {
                printf("<html><body>\n");
                printf("<h1>Invalid credentials</h1>\n");
                printf("<a href=\"/login\">Try again</a>\n");
                printf("</body></html>");
            }
        }
    } else if (strcmp(path, "/secret") == 0) {
        // Simulate session check
        const char *session_username = getenv("HTTP_COOKIE");
        if (session_username != NULL && strstr(session_username, "username=admin")) {
            printf("<html><body>\n");
            printf("<h1>Secret Settings</h1>\n");
            printf("</body></html>");
        } else {
            redirectTo("/login");
        }
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    const char *method = getenv("REQUEST_METHOD");
    const char *path = getenv("PATH_INFO");

    if (strcmp(method, "POST") == 0) {
        size_t buf_len = 4096;
        char buf[buf_len];
        FILE *input_stream = fopen("php://input", "r");
        fread(buf, sizeof(char), buf_len - 1, input_stream);
        fclose(input_stream);

        buf[strcspn(buf, "\r\n")] = '\0'; // Remove trailing newlines

        char username[100], password[100];
        sscanf(buf, "username=%99[^&]&password=%99s", username, password);
        
        handleRequest(path, method, username, password);
    } else {
        handleRequest(path, method);
    }

    return 0;
}