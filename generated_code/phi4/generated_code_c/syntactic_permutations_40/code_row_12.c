#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple web server simulation using C (not real HTTP handling)
void send_response(const char *status, const char *content_type, const char *body) {
    printf("HTTP/1.1 %s\n", status);
    printf("Content-Type: %s\n\n", content_type);
    printf("%s\n", body);
}

typedef struct {
    char username[50];
    char email[100];
    char ssn[12]; // Assuming SSN format "000-00-0000"
} Session;

Session session = {"user123", "user@example.com", "123-45-6789"};

void info() {
    char body[256];
    snprintf(body, sizeof(body), "<html><body>"
                                 "<h1>User Info</h1>"
                                 "<p>Username: %s</p>"
                                 "<p>Email: %s</p>"
                                 "<p>Last 4 Digits of SSN: %c%c%c%c</p>"
                                 "</body></html>",
             session.username,
             session.email,
             session.ssn[6], session.ssn[7], session.ssn[8], session.ssn[9]);
    send_response("200 OK", "text/html", body);
}

void handle_request(const char *request) {
    if (strcmp(request, "GET /info") == 0) {
        info();
    } else {
        send_response("404 Not Found", "text/plain", "Not Found");
    }
}

int main() {
    const char *requests[] = {"GET /info", "GET /unknown"};
    int num_requests = sizeof(requests) / sizeof(requests[0]);

    for (int i = 0; i < num_requests; ++i) {
        handle_request(requests[i]);
        printf("--------------------------------------------------\n");
    }

    return 0;
}