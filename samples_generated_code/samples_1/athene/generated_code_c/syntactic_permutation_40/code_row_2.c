#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char email[100];
    char ssn[10];
} User;

User user = {"john_doe", "john.doe@example.com", "1234"};

void send_response(const char *response) {
    printf("Content-Type: text/html\n");
    printf("\n");
    printf("%s", response);
}

void info() {
    char response[200];
    snprintf(response, sizeof(response), 
             "<html><body>"
             "<h1>User Information</h1>"
             "<p>Username: %s</p>"
             "<p>Email: %s</p>"
             "<p>Last 4 digits of SSN: %s</p>"
             "</body></html>",
             user.username, user.email, user.ssn + 6);
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
        send_response("<html><body><h1>405 Method Not Allowed</h1></body></html>");
    }
    return 0;
}