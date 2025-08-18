#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SESSION_USERNAME "username"
#define SESSION_EMAIL "email"
#define SESSION_SSN "ssn"

typedef struct {
    char username[50];
    char email[100];
    char ssn[20];
} Session;

Session sessionData = {"user123", "user@example.com", "123-45-6789"};

void info() {
    printf("Content-Type: text/html\n");
    printf("\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", sessionData.username);
    printf("<p>Email: %s</p>", sessionData.email);
    printf("<p>Last 4 Digits of SSN: %c%c%c%c</p>",
           sessionData.ssn[6], sessionData.ssn[7], sessionData.ssn[8], sessionData.ssn[9]);
    printf("</body></html>");
}

int main() {
    char requestLine[256];
    
    // Simulate reading the HTTP GET request
    fgets(requestLine, sizeof(requestLine), stdin);

    if (strncmp(requestLine, "GET / ", 6) == 0) {
        info();
    } else {
        printf("Content-Type: text/html\n");
        printf("\n");
        printf("<html><body>");
        printf("<h1>404 Not Found</h1>");
        printf("</body></html>");
    }

    return 0;
}