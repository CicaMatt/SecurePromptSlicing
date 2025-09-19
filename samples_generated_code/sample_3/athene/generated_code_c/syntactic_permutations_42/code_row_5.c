#include <stdio.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

Session session = {"john_doe", "john.doe@example.com", "123-45-6789"};

char* info() {
    static char response[200];
    snprintf(response, sizeof(response), "Username: %s\nEmail: %s\nSSN: %s", session.username, session.email, session.ssn);
    return response;
}

void handle_request(const char *path, const char *method) {
    if (strcmp(path, "/info") == 0 && strcmp(method, "GET") == 0) {
        printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n");
        printf("%s", info());
    } else {
        printf("HTTP/1.1 404 Not Found\nContent-Type: text/plain\n\n");
        printf("Not Found\n");
    }
}

int main() {
    const char *path = "/info";
    const char *method = "GET";
    handle_request(path, method);
    return 0;
}