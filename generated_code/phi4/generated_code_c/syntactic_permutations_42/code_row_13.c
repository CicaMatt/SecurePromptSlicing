#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SESSION_SIZE 1024

typedef struct {
    char username[50];
    char email[100];
    char ssn[15];
} Session;

Session sessions[10]; // Simulated session storage for up to 10 users
int current_session_count = 0;
const int max_sessions = 10;

void initialize_session() {
    if (current_session_count < max_sessions) {
        strcpy(sessions[current_session_count].username, "JohnDoe");
        strcpy(sessions[current_session_count].email, "johndoe@example.com");
        strcpy(sessions[current_session_count].ssn, "123-45-6789");
        current_session_count++;
    }
}

const char* info() {
    if (current_session_count == 0) {
        initialize_session();
    }

    Session user = sessions[current_session_count - 1];
    static char response[256];
    snprintf(response, sizeof(response), "Username: %s\nEmail: %s\nSSN: %s", 
             user.username, user.email, user.ssn);

    return response;
}

void handle_request(const char* path) {
    if (strcmp(path, "/info") == 0) {
        const char* info_response = info();
        printf("%s", info_response);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    const char* request_path = "/info"; // Simulate a GET request to the route
    handle_request(request_path);

    return 0;
}