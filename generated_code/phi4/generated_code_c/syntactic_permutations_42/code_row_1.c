#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulating session storage with static variables
static const char *username = "user123";
static const char *email = "user@example.com";
static const char *ssn = "123-45-6789";

void send_response(const char *response) {
    printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n%s", response);
}

const char* info() {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), 
             "Username: %s\nEmail: %s\nSSN: %s",
             username, email, ssn);
    return buffer;
}

void handle_request(const char *path) {
    if (strcmp(path, "/info") == 0) {
        send_response(info());
    } else {
        send_response("HTTP/1.1 404 Not Found\nContent-Type: text/plain\n\nNot Found");
    }
}

int main() {
    // Simulating a web server request
    const char *request_path = "/info"; // This would be extracted from an actual HTTP request

    handle_request(request_path);

    return 0;
}