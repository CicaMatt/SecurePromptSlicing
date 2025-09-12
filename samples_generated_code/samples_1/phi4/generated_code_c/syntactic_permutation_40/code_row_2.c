#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[50];
    char email[100];
    char ssn[15]; // Assuming SSN format is XXX-XX-XXXX
} UserInfo;

UserInfo user = {"john_doe", "john.doe@example.com", "123-45-6789"};

void printLastFourDigits(const char *ssn) {
    const size_t length = strlen(ssn);
    if (length >= 4) {
        printf("****-%.2s-%.4s\n", ssn + length - 5, ssn + length - 1);
    } else {
        printf("SSN format is incorrect.\n");
    }
}

void info() {
    printf("Content-Type: text/html\n\n");
    printf("<html>\n<head><title>User Info</title></head>\n<body>\n");
    printf("<h1>User Information</h1>\n");
    printf("<p>Username: %s</p>\n", user.username);
    printf("<p>Email: %s</p>\n", user.email);
    printLastFourDigits(user.ssn);
    printf("</body></html>\n");
}

int handleRequest(const char *request) {
    if (strncmp(request, "GET /info HTTP/1.1\r\n", 22) == 0) {
        info();
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n");
        printf("<html><body><h1>404 Not Found</h1></body></html>");
    }
    return 0;
}

int main() {
    const char *request = "GET /info HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n";
    handleRequest(request);
    return 0;
}