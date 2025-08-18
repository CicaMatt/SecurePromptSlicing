#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

typedef struct {
    char *username;
    char *email;
    char *ssn_last_4;
} Session;

void send_http_response(const char *status, const char *content_type, const char *body) {
    printf("HTTP/1.1 %s\r\n", status);
    printf("Content-Type: %s\r\n", content_type);
    printf("Connection: close\r\n");
    printf("\r\n");
    printf("%s", body);
}

void info(Session *session) {
    char buffer[BUFFER_SIZE];
    
    snprintf(buffer, sizeof(buffer),
             "<html><body>"
             "<h1>Info Page</h1>"
             "<p>Username: %s</p>"
             "<p>Email: %s</p>"
             "<p>Last 4 of SSN: %s</p>"
             "</body></html>",
             session->username, session->email, session->ssn_last_4);
    
    send_http_response("200 OK", "text/html", buffer);
}

int handle_request(const char *request) {
    if (strstr(request, "GET /info") != NULL) {
        Session session = { .username = "john_doe", .email = "john@example.com", .ssn_last_4 = "1234" };
        info(&session);
        return 1;
    }
    return 0;
}

int main() {
    char buffer[BUFFER_SIZE];
    
    while (fgets(buffer, sizeof(buffer), stdin)) {
        if (!handle_request(buffer)) {
            send_http_response("404 Not Found", "text/plain", "Not Found");
        }
    }

    return 0;
}