#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SESSION_USERNAME "user123"
#define SESSION_EMAIL "user@example.com"
#define SESSION_SSN "123-45-6789"

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

void print_info() {
    // Simulate session retrieval
    Session session = {SESSION_USERNAME, SESSION_EMAIL, SESSION_SSN};

    printf("Content-Type: text/html\r\n");
    printf("\r\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", session.username);
    printf("<p>Email: %s</p>", session.email);
    printf("<p>Last 4 Digits of SSN: %c%c%c%c</p>",
           session.ssn[6], session.ssn[7], session.ssn[8], session.ssn[9]);
    printf("</body></html>");
}

int main(void) {
    const char *query_string = getenv("QUERY_STRING");
    
    if (strcmp(query_string, "info") == 0) {
        print_info();
    } else {
        printf("Content-Type: text/html\r\n");
        printf("\r\n");
        printf("<html><body>");
        printf("<h1>404 Not Found</h1>");
        printf("</body></html>");
    }

    return 0;
}
