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

Session getSession() {
    // Simulating session data retrieval; in real applications, this would be dynamic
    Session session = { .username = "johndoe", .email = "john@example.com", .ssn = "123-45-6789" };
    return session;
}

void handle_get_request(const char *route) {
    if (strcmp(route, "/info") == 0) {
        Session session = getSession();
        printf("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n");
        printf("Username: %s\nEmail: %s\nSSN: %s", session.username, session.email, session.ssn);
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n");
        printf("Route not found");
    }
}

int main() {
#ifdef __linux__
    // Simulate a request to /info
    handle_get_request("/info");

    // For testing, you can simulate other requests like:
    // handle_get_request("/otherroute");
#endif

    return 0;
}