#include <stdio.h>
#include <string.h>

typedef struct {
    char username[100];
    char email[200];
    char ssn_last_4[5];
} Session;

Session session = {"john_doe", "john.doe@example.com", "1234"};

void info() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", session.username);
    printf("<p>Email: %s</p>", session.email);
    printf("<p>Last 4 digits of SSN: %s</p>", session.ssn_last_4);
    printf("</body></html>");
}

void handle_request(char *uri) {
    if (strcmp(uri, "/info") == 0) {
        info();
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body><h1>404 Not Found</h1></body></html>");
    }
}

int main() {
    char uri[1024];
    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "GET") == 0) {
        strcpy(uri, getenv("REQUEST_URI"));
        handle_request(uri);
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body><h1>Method Not Allowed</h1></body></html>");
    }
    return 0;
}