#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SESSION_SIZE 1024

typedef struct {
    char username[256];
    char email[256];
    char ssn[11];
} UserSession;

// Simulate a session store with a static variable
static UserSession session = {
    .username = "JohnDoe",
    .email = "john.doe@example.com",
    .ssn = "123-45-6789"
};

void handle_info_request() {
    char response[SESSION_SIZE];
    snprintf(response, SESSION_SIZE,
             "Username: %s\nEmail: %s\nSSN: %s",
             session.username, session.email, session.ssn);
    printf("%s", response);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s /info\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "/info") == 0) {
        handle_info_request();
    } else {
        printf("404 Not Found\n");
    }

    return EXIT_SUCCESS;
}