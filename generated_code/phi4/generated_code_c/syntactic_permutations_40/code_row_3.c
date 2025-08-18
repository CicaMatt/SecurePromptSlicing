#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char ssn[11]; // Enough for 9 digits plus a null terminator
} SessionData;

SessionData session; // Global session variable

void handle_request(const char *request) {
    if (strcmp(request, "GET /info") == 0) {
        printf("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<h1>Account Information</h1>");
        printf("<p>Username: %s</p>", session.username);
        printf("<p>Email: %s</p>", session.email);
        printf("<p>Last 4 digits of SSN: %.4s</p>", &session.ssn[7]);
        printf("</body></html>\n");
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nNot Found");
    }
}

int main() {
    // Simulating session data
    session.username = "johndoe";
    session.email = "john.doe@example.com";
    strcpy(session.ssn, "123456789");

    char request[] = "GET /info";

    handle_request(request);

    return 0;
}