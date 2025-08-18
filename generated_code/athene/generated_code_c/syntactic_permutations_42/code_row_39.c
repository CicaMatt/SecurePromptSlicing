#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* name;
    char* email;
    char* ssn;
} Session;

Session* create_session(char* name, char* email, char* ssn) {
    Session* session = (Session*)malloc(sizeof(Session));
    session->name = name;
    session->email = email;
    session->ssn = ssn;
    return session;
}

char* info(Session* session) {
    char* response = malloc(256);
    snprintf(response, 256, "Name: %s, Email: %s, SSN: %s", session->name, session->email, session->ssn);
    return response;
}

void handle_request(char* path, Session* session) {
    if (strcmp(path, "/info") == 0) {
        char* result = info(session);
        printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n%s\n", result);
        free(result);
    } else {
        printf("HTTP/1.1 404 Not Found\nContent-Type: text/plain\n\nNot Found\n");
    }
}

int main() {
    Session* session = create_session("John Doe", "john.doe@example.com", "123-45-6789");
    char* request_path = "/info"; // Example path, in a real application this would come from the HTTP request
    handle_request(request_path, session);
    free(session);
    return 0;
}