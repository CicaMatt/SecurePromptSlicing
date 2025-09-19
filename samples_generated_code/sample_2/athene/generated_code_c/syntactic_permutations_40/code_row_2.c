#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char email[100];
    char ssn[10];
} User;

User user = {"john_doe", "john.doe@example.com", "1234"};

void send_response(const char *response) {
    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: text/html\r\n");
    printf("\r\n");
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
             user.username, user.email, &user.ssn[6]);
    send_response(response);
}

int main() {
    char request[] = "GET /info HTTP/1.1";
    if (strcmp(request, "GET /info HTTP/1.1") == 0) {
        info();
    } else {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/html\r\n");
        printf("\r\n");
        printf("<html><body><h1>404 - Page Not Found</h1></body></html>");
    }
    return 0;
}