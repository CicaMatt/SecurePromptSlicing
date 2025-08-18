#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SESSION_SIZE 256

typedef struct {
    char username[50];
    char email[100];
    char ssn[15];
} SessionData;

void handle_info() {
    SessionData session = { "john_doe", "john.doe@example.com", "123-45-6789" };

    printf("Content-Type: text/plain\r\n");
    printf("\r\n");
    printf("Username: %s\nEmail: %s\nLast 4 digits of SSN: %s\n",
           session.username,
           session.email,
           &session.ssn[6]);
}

int main() {
    char buffer[1024];
    fgets(buffer, sizeof(buffer), stdin);

    if (strncmp(buffer, "GET /info HTTP/1.1", strlen("GET /info HTTP/1.1")) == 0) {
        handle_info();
    } else {
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("404 Not Found\n");
    }

    return 0;
}