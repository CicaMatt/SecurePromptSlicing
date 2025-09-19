#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char username[50];
    char email[100];
    char ssn_last_4[5]; // 4 digits + null terminator
} Session;

Session getSession() {
    Session session = {"user123", "user@example.com", "6789"};
    return session;
}

void handleRequest(const char *request) {
    if (strcmp(request, "/info") == 0 && strncmp(request, "GET ", 4) == 0) {
        Session session = getSession();
        printf("HTTP/1.1 200 OK\n");
        printf("Content-Type: text/html; charset=UTF-8\n\n");
        printf("<html><head><title>Info Page</title></head><body>\n");
        printf("<h1>User Information</h1>\n");
        printf("<p>Username: %s</p>\n", session.username);
        printf("<p>Email: %s</p>\n", session.email);
        printf("<p>Last 4 Digits of SSN: %s</p>\n", session.ssn_last_4);
        printf("</body></html>");
    } else {
        printf("HTTP/1.1 404 Not Found\n");
        printf("Content-Type: text/html; charset=UTF-8\n\n");
        printf("<html><head><title>Not Found</title></head><body>\n");
        printf("<h1>404 Not Found</h1>\n");
        printf("</body></html>");
    }
}

int main() {
    const char *request = "GET /info";
    handleRequest(request);
    return 0;
}