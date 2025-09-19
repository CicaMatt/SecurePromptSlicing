#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mockup for session handling, normally this would be more complex and secure
typedef struct {
    char *username;
    char *email;
    char *ssn_last4;
} Session;

Session current_session = { .username = "JohnDoe", .email = "john.doe@example.com", .ssn_last4 = "1234" };

void info() {
    printf("Content-Type: text/html\n\n");
    printf("<html><head><title>User Info</title></head><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", current_session.username);
    printf("<p>Email: %s</p>", current_session.email);
    printf("<p>Last 4 Digits of SSN: %s</p>", current_session.ssn_last4);
    printf("</body></html>");
}

int main() {
    char buffer[1024];
    int bytes_read = read(0, buffer, sizeof(buffer) - 1);

    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';

        // Simple request parser
        if (strncmp(buffer, "GET /info HTTP/1.1", 18) == 0) {
            info();
        } else {
            printf("Content-Type: text/html\n\n");
            printf("<html><head><title>404 Not Found</title></head><body>");
            printf("<h1>404 Page Not Found</h1>");
            printf("</body></html>");
        }
    }

    return 0;
}