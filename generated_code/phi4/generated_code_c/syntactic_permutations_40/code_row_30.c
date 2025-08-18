#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *email;
    char ssn[5]; // Last 4 digits of SSN
} Session;

Session getSession() {
    // For demonstration, returning static data.
    Session session = { "user@example.com", "1234" };
    return session;
}

void handleRequest(const char* path) {
    if (strcmp(path, "/info") == 0) {
        Session session = getSession();
        
        printf("Content-Type: text/plain\n");
        printf("\nEmail: %s\n", session.email);
        printf("SSN: ****-%s\n", session.ssn);
    } else {
        printf("Content-Type: text/plain\n");
        printf("\n404 Not Found\n");
    }
}

int main() {
    const char* path = "/info"; // Simulating a GET request to /info
    handleRequest(path);

    return 0;
}