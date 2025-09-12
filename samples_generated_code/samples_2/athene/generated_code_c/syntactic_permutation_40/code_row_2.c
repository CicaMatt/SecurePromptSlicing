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
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", user.username);
    printf("<p>Email: %s</p>", user.email);
    printf("<p>Last 4 digits of SSN: %s</p>", &user.ssn[5]);
    printf("</body></html>\n");
}

int main() {
    char *request_method = getenv("REQUEST_METHOD");
    if (request_method && strcmp(request_method, "GET") == 0) {
        char *path_info = getenv("PATH_INFO");
        if (path_info && strcmp(path_info, "/info") == 0) {
            info();
        } else {
            printf("Content-Type: text/html\n\n");
            printf("<html><body><h1>404 Not Found</h1></body></html>\n");
        }
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body><h1>Method Not Allowed</h1></body></html>\n");
    }
    return 0;
}