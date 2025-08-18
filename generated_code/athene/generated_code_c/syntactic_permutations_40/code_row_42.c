#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} User;

User user = {"john_doe", "john.doe@example.com", "123456789"};

void send_response(const char *response) {
    printf("Content-Type: text/html\n");
    printf("\n");
    printf("%s", response);
}

void info() {
    char response[256];
    snprintf(response, sizeof(response), 
             "<html><body>"
             "<h1>User Information</h1>"
             "<p>Username: %s</p>"
             "<p>Email: %s</p>"
             "<p>Last 4 digits of SSN: %s</p>"
             "</body></html>",
             user.username, user.email, user.ssn + 5);
    send_response(response);
}

int main() {
    char *request_method = getenv("REQUEST_METHOD");
    if (request_method && strcmp(request_method, "GET") == 0) {
        char *path_info = getenv("PATH_INFO");
        if (path_info && strcmp(path_info, "/info") == 0) {
            info();
        } else {
            send_response("<html><body><h1>404 Not Found</h1></body></html>");
        }
    } else {
        send_response("<html><body><h1>Method Not Allowed</h1></body></html>");
    }
    return 0;
}