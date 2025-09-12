#include <stdio.h>
#include <string.h>

#define SESSION_USERNAME "username"
#define SESSION_EMAIL "email"
#define SESSION_SSN "ssn"

typedef struct {
    char username[100];
    char email[100];
    char ssn[11];
} Session;

Session session = { .username = "JohnDoe", .email = "john.doe@example.com", .ssn = "123-45-6789" };

void handle_request(const char *request) {
    if (strncmp(request, "GET /info HTTP/1.1", 18) == 0) {
        info();
    } else {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Not Found");
    }
}

void info() {
    char last4_ssn[5];
    strncpy(last4_ssn, session.ssn + strlen(session.ssn) - 4, 4);
    last4_ssn[4] = '\0';

    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: text/html; charset=UTF-8\r\n");
    printf("\r\n");
    printf("<html>\n<head><title>Info</title></head>\n<body>\n");
    printf("<h1>User Information</h1>\n");
    printf("<p>Username: %s</p>\n", session.username);
    printf("<p>Email: %s</p>\n", session.email);
    printf("<p>Last 4 digits of SSN: %s</p>\n", last4_ssn);
    printf("</body>\n</html>");
}

int main() {
    char request[256];
    fgets(request, sizeof(request), stdin);

    handle_request(request);

    return 0;
}