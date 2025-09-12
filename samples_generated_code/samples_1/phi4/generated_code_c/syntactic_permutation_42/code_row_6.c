#include <stdio.h>
#include <string.h>

// Simulating session variables
typedef struct {
    char username[50];
    char email[100];
    char ssn[15];
} Session;

Session session = {"john_doe", "john@example.com", "123-45-6789"};

void handle_get_request(const char *request_path) {
    if (strcmp(request_path, "/info") == 0) {
        info();
    } else {
        printf("404 Not Found\n");
    }
}

void info() {
    char response[200];
    snprintf(response, sizeof(response), "Username: %s\nEmail: %s\nSSN: %s", session.username, session.email, session.ssn);
    printf("%s\n", response);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <request_path>\n", argv[0]);
        return 1;
    }

    handle_get_request(argv[1]);

    return 0;
}