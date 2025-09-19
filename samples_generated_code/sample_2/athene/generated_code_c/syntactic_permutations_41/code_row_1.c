#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REQUEST_SIZE 1024

typedef struct {
    char *username;
    char *email;
    char *ssn;
} User;

User user = {"john_doe", "john.doe@example.com", "123-45-6789"};

void handle_request(char *request) {
    if (strstr(request, "GET /info") == request) {
        printf("HTTP/1.1 200 OK\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>\n");
        printf("<h1>User Information</h1>\n");
        printf("<p>Username: %s</p>\n", user.username);
        printf("<p>Email: %s</p>\n", user.email);
        printf("<p>SSN: %s</p>\n", user.ssn);
        printf("</body></html>\n");
    } else {
        printf("HTTP/1.1 404 Not Found\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>\n");
        printf("<h1>Not Found</h1>\n");
        printf("</body></html>\n");
    }
}

int main() {
    char request[MAX_REQUEST_SIZE];
    while (1) {
        fgets(request, MAX_REQUEST_SIZE, stdin);
        handle_request(request);
    }
    return 0;
}