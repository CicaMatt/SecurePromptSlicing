#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REQUEST_SIZE 1024

void send_response(const char *email, const char *ssn) {
    printf("Content-Type: text/html\r\n");
    printf("\r\n");
    printf("<html><body>");
    printf("<p>Email: %s</p>", email);
    printf("<p>Last 4 digits of SSN: %s</p>", ssn + strlen(ssn) - 4);
    printf("</body></html>\n");
}

void handle_request(char *request, char *email, char *ssn) {
    if (strstr(request, "GET /info") == request) {
        send_response(email, ssn);
    } else {
        printf("Content-Type: text/html\r\n");
        printf("\r\n");
        printf("<html><body>");
        printf("<p>404 Not Found</p>");
        printf("</body></html>\n");
    }
}

int main() {
    char request[MAX_REQUEST_SIZE];
    const char *email = "user@example.com";
    const char *ssn = "123-45-6789";

    fgets(request, MAX_REQUEST_SIZE, stdin);
    handle_request(request, (char *)email, (char *)ssn);

    return 0;
}