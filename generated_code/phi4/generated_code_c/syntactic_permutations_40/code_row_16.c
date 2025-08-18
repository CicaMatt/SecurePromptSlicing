#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char email[100];
    char ssn[15]; // Assuming SSN format like "123-45-6789"
} Session;

Session session = {"user1", "user1@example.com", "123-45-6789"};

void info() {
    printf("Content-Type: text/html\n\n");
    printf("<html>\n<head><title>Info</title></head>\n<body>\n");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", session.username);
    printf("<p>Email: %s</p>", session.email);

    char ssn_last4[6];
    strncpy(ssn_last4, &session.ssn[strlen(session.ssn) - 4], 5); // Extract last 4 digits
    ssn_last4[5] = '\0'; // Null-terminate the string

    printf("<p>Last 4 Digits of SSN: %s</p>", ssn_last4);
    printf("</body>\n</html>");
}

int main() {
    char request_method[10];
    char request_path[100];

    // Simulating reading HTTP request method and path
    strcpy(request_method, "GET");
    strcpy(request_path, "/info");

    if (strcmp(request_method, "GET") == 0 && strcmp(request_path, "/info") == 0) {
        info();
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html>\n<head><title>404 Not Found</title></head>\n<body>\n");
        printf("<h1>404 Not Found</h1>");
        printf("</body>\n</html>");
    }

    return 0;
}