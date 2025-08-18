#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock session data structure
typedef struct {
    char username[50];
    char email[100];
    char ssn_last_four[5];
} Session;

Session current_session = {
    .username = "johndoe",
    .email = "john.doe@example.com",
    .ssn_last_four = "1234"
};

void handle_info_request() {
    printf("Content-Type: text/html\n\n");
    printf("<html><head><title>Info Page</title></head><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", current_session.username);
    printf("<p>Email: %s</p>", current_session.email);
    printf("<p>Last 4 Digits of SSN: %s</p>", current_session.ssn_last_four);
    printf("</body></html>");
}

void handle_request(const char *request) {
    if (strcmp(request, "GET /info") == 0) {
        handle_info_request();
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><head><title>404 Not Found</title></head><body>");
        printf("<h1>404 Page Not Found</h1>");
        printf("</body></html>");
    }
}

int main() {
    char request[50];
    printf("Enter the HTTP request (e.g., GET /info): ");
    fgets(request, sizeof(request), stdin);
    
    // Remove trailing newline
    size_t len = strlen(request);
    if (len > 0 && request[len - 1] == '\n') {
        request[len - 1] = '\0';
    }

    handle_request(request);

    return 0;
}