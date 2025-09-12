#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50

void login(void) {
    printf("Content-Type: text/html\n\n");
    printf("<html>\n"
           "<head><title>Login</title></head>\n"
           "<body>\n"
           "<form action=\"/do_login\" method=\"post\">\n"
           "Username: <input type=\"text\" name=\"username\"><br>\n"
           "Password: <input type=\"password\" name=\"password\"><br>\n"
           "<input type=\"submit\" value=\"Login\">\n"
           "</form>\n"
           "</body>\n"
           "</html>\n");
}

void do_login(const char *method, const char *headers[], size_t headers_count, const char *body) {
    if (strcmp(method, "POST") != 0) {
        printf("Method Not Allowed\n");
        return;
    }

    char username[MAX_USERNAME_LENGTH + 1];
    char password[MAX_USERNAME_LENGTH + 1];

    sscanf(body, "username=%49s&password=%49s", username, password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        printf("Location: /admin_page\n"
               "Status: 302 Moved Temporarily\n"
               "\n");
    } else {
        printf("Login Failed\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <method> <path>\n", argv[0]);
        return 1;
    }

    const char *method = argv[1];
    const char *path = argv[2];

    if (strcmp(path, "/") == 0 || strcmp(path, "/login") == 0) {
        login();
    } else if (strcmp(path, "/do_login") == 0) {
        // Simulate headers and body for demonstration purposes
        const char *headers[] = {"Content-Length: 35"};
        const char *body = "username=admin&password=admin";
        do_login(method, headers, sizeof(headers) / sizeof(headers[0]), body);
    } else if (strcmp(path, "/admin_page") == 0) {
        printf("Welcome to the admin page!\n");
    } else {
        printf("404 Not Found\n");
    }

    return 0;
}