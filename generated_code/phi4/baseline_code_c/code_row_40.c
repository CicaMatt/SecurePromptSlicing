#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SESSION_USERNAME "user123"
#define SESSION_EMAIL    "user@example.com"
#define SESSION_SSN      "123-45-6789"

void info() {
    char username[] = SESSION_USERNAME;
    char email[] = SESSION_EMAIL;
    char ssn[] = SESSION_SSN;

    printf("Content-Type: text/html\r\n");
    printf("\r\n");
    printf("<html><head><title>Info</title></head><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", username);
    printf("<p>Email: %s</p>", email);
    printf("<p>Last 4 digits of SSN: %.4s</p>", ssn + strlen(ssn) - 4);
    printf("</body></html>");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s /info\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "/info") == 0) {
        info();
    } else {
        printf("404 Not Found\r\n");
    }
    
    return 0;
}