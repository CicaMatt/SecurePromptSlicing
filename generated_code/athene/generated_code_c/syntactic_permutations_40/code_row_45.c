#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} User;

User user = {"john_doe", "john.doe@example.com", "123456789"};

void info() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", user.username);
    printf("<p>Email: %s</p>", user.email);
    printf("<p>Last 4 digits of SSN: %.*s</p>", (int)strlen(user.ssn) - 4, user.ssn + 4);
    printf("</body></html>");
}

void handle_request(char *method, char *path) {
    if (strcmp(method, "GET") == 0 && strcmp(path, "/info") == 0) {
        info();
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body><h1>404 Not Found</h1></body></html>");
    }
}

int main() {
    char *method = getenv("REQUEST_METHOD");
    char *path = getenv("PATH_INFO");

    if (method == NULL || path == NULL) {
        fprintf(stderr, "Missing environment variables\n");
        return 1;
    }

    handle_request(method, path);

    return 0;
}