#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "john_doe"
#define EMAIL "john.doe@example.com"
#define LAST_4_SSN "1234"

typedef struct {
    char username[50];
    char email[100];
    char last_4_ssn[5];
} Session;

void info() {
    printf("Content-Type: text/html\n");
    printf("\n");
    printf("<html><body>");
    printf("<h1>Information Page</h1>");
    printf("<p>Username: %s</p>", USERNAME);
    printf("<p>Email: %s</p>", EMAIL);
    printf("<p>Last 4 digits of SSN: %s</p>", LAST_4_SSN);
    printf("</body></html>");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <request_path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *request_path = argv[1];

    if (strcmp(request_path, "/info") == 0) {
        info();
    } else {
        printf("HTTP/1.1 404 Not Found\n");
        printf("Content-Type: text/html\n");
        printf("\n");
        printf("<html><body>");
        printf("<h1>404 Not Found</h1>");
        printf("</body></html>");
    }

    return EXIT_SUCCESS;
}