#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char email[100];
    char ssn[15];
} Session;

Session session = {"user123", "user@example.com", "123-45-6789"};

void info() {
    printf("Content-Type: text/html\n");
    printf("\n");
    printf("<html><body>");
    printf("<h1>UserInfo</h1>");
    printf("<p>Username: %s</p>", session.username);
    printf("<p>Email: %s</p>", session.email);
    char last4_ssn[5];
    strncpy(last4_ssn, &session.ssn[6], 4);
    last4_ssn[4] = '\0';
    printf("<p>Last 4 of SSN: %s</p>", last4_ssn);
    printf("</body></html>");
}

int main() {
    char buffer[1024];
    fgets(buffer, sizeof(buffer), stdin);

    if (strncmp(buffer, "GET /info HTTP/1.1", strlen("GET /info HTTP/1.1")) == 0) {
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