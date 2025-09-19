#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SESSION_SIZE 1024

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

Session session_data = {"user123", "user@example.com", "123-45-6789"};

void handle_request(const char* request) {
    if (strcmp(request, "/info") == 0) {
        printf("Content-Type: text/plain\n\n");
        printf("Username: %s\nEmail: %s\nSSN: %s\n",
               session_data.username,
               session_data.email,
               session_data.ssn);
    } else {
        printf("Content-Type: text/plain\n\n");
        printf("404 Not Found\n");
    }
}

int main(int argc, char *argv[]) {
    char buffer[SESSION_SIZE];
    
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <request>\n", argv[0]);
        return EXIT_FAILURE;
    }

    strncpy(buffer, argv[1], SESSION_SIZE - 1);
    buffer[SESSION_SIZE - 1] = '\0';

    handle_request(buffer);

    return EXIT_SUCCESS;
}