#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SESSION_SIZE 1024

typedef struct {
    char username[100];
    char email[100];
    char ssn[20];
} SessionData;

SessionData session = {"JohnDoe", "john.doe@example.com", "123-45-6789"};

void handle_get_request(const char *path) {
    if (strcmp(path, "/info") == 0) {
        info();
    } else {
        printf("404 Not Found\n");
    }
}

void info() {
    char response[SESSION_SIZE];
    snprintf(response, sizeof(response),
             "Username: %s\nEmail: %s\nSSN: %s",
             session.username,
             session.email,
             session.ssn);
    printf("%s", response);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <request_path>\n", argv[0]);
        return 1;
    }

    handle_get_request(argv[1]);

    return 0;
}