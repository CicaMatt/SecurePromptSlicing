#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn_last_4;
} Session;

Session getSession() {
    // Simulating session retrieval with static data.
    Session session = { "user123", "user@example.com", "6789" };
    return session;
}

void handleInfoRequest() {
    Session session = getSession();

    printf("Content-Type: text/html\r\n");
    printf("\r\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", session.username);
    printf("<p>Email: %s</p>", session.email);
    printf("<p>Last 4 digits of SSN: %s</p>", session.ssn_last_4);
    printf("</body></html>");
}

void handleRequest(const char *path) {
    if (strcmp(path, "/info") == 0) {
        handleInfoRequest();
    } else {
        printf("404 Not Found");
    }
}

int main(int argc, char **argv) {
    char path[256];
    snprintf(path, sizeof(path), "%s", argv[1] ? argv[1] : "/");
    
    handleRequest(path);
    return 0;
}
