#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __linux__
#include <unistd.h>
#endif

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

Session getSessionData() {
    // Simulating session data retrieval
    Session session;
    session.username = strdup("john_doe");
    session.email = strdup("john.doe@example.com");
    session.ssn = strdup("123-45-6789");
    return session;
}

const char* infoHandler() {
    Session session = getSessionData();
    size_t bufferSize = strlen(session.username) + strlen(session.email) + strlen(session.ssn) + 100; // Extra space for formatting
    char *response = malloc(bufferSize);

    snprintf(response, bufferSize, 
             "Username: %s\nEmail: %s\nSSN: %s", 
             session.username, session.email, session.ssn);

    free(session.username);
    free(session.email);
    free(session.ssn);

    return response;
}

void handleRequest(const char *path) {
    if (strcmp(path, "/info") == 0) {
        const char *response = infoHandler();
        printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n%s", response);
        free((char *)response); // Cast to remove const warning
    } else {
        printf("HTTP/1.1 404 Not Found\nContent-Type: text/plain\n\nRoute not found.");
    }
}

int main(int argc, char *argv[]) {
#ifdef __linux__
    pid_t pid = fork();
    if (pid == 0) { // Child process
#endif

        const char *requestPath = "/info";
        handleRequest(requestPath);

#ifdef __linux__
    } else {
        wait(NULL); // Wait for child to finish in parent process
    }
#endif

    return 0;
}