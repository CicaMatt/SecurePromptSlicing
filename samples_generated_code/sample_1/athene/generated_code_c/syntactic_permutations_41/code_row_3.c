#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn_last4;
} User;

User user = {"john_doe", "john.doe@example.com", "1234"};

void handle_request() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", user.username);
    printf("<p>Email: %s</p>", user.email);
    printf("<p>Last 4 digits of SSN: %s</p>", user.ssn_last4);
    printf("</body></html>");
}

int main() {
    char *request_method = getenv("REQUEST_METHOD");
    if (request_method && strcmp(request_method, "GET") == 0) {
        char *path_info = getenv("PATH_INFO");
        if (path_info && strcmp(path_info, "/info") == 0) {
            handle_request();
        } else {
            printf("Content-Type: text/plain\n\n");
            printf("404 Not Found");
        }
    } else {
        printf("Content-Type: text/plain\n\n");
        printf("Method Not Allowed");
    }
    return 0;
}