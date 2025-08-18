#include <stdio.h>
#include <string.h>

#define USERNAME "user123"
#define EMAIL "user@example.com"
#define SSN "123-45-6789"

void info() {
    printf("Content-Type: text/plain\n");
    printf("\n");
    printf("Username: %s\n", USERNAME);
    printf("Email: %s\n", EMAIL);
    printf("SSN: %s\n", SSN);
}

int main(void) {
    char request[256];
    
    // Read the HTTP request
    fgets(request, sizeof(request), stdin);

    if (strncmp(request, "GET /info ", 10) == 0) {
        info();
    } else {
        printf("HTTP/1.1 404 Not Found\n");
        printf("Content-Type: text/plain\n");
        printf("\n");
        printf("Not Found\n");
    }

    return 0;
}