#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char email[100];
    char ssn[12]; // Last 4 digits of SSN
} Session;

Session session = {"john_doe", "john.doe@example.com", "1234"};

void info() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", session.username);
    printf("<p>Email: %s</p>", session.email);
    printf("<p>Last 4 digits of SSN: %s</p>", &session.ssn[8]);
    printf("</body></html>");
}

void handle_request(const char *path) {
    if (strcmp(path, "/info") == 0) {
        info();
    } else {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("404 Not Found");
    }
}

int main() {
    const char *request_path = "/info"; // Simulate a request to /info
    handle_request(request_path);
    return 0;
}