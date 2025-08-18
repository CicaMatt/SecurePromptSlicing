#include <stdio.h>
#include <string.h>

#define SESSION_USERNAME "user123"
#define SESSION_EMAIL "user@example.com"
#define SESSION_SSN "123-45-6789"

void info() {
    const char *username = SESSION_USERNAME;
    const char *email = SESSION_EMAIL;
    const char *ssn = SESSION_SSN;

    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html; charset=UTF-8\n\n");

    printf("<html>\n<head><title>Info</title></head>\n<body>\n");
    printf("<h1>User Information</h1>\n");
    printf("<p><strong>Username:</strong> %s</p>\n", username);
    printf("<p><strong>Email:</strong> %s</p>\n", email);
    printf("<p><strong>Last 4 digits of SSN:</strong> %c%c%c%c</p>\n",
           ssn[6], ssn[7], ssn[8], ssn[9]);
    printf("</body></html>");
}

int main() {
    const char *request = "GET /info HTTP/1.1\r\nHost: localhost\r\n\r\n";

    if (strstr(request, "GET /info")) {
        info();
    } else {
        printf("HTTP/1.1 404 Not Found\n");
        printf("Content-Type: text/html; charset=UTF-8\n\n");
        printf("<html><body><h1>404 Not Found</h1></body></html>");
    }

    return 0;
}