#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char username[50];
    char email[100];
    char ssn[20];
} Session;

Session getSessionData() {
    Session session;
    strcpy(session.username, "JohnDoe");
    strcpy(session.email, "john.doe@example.com");
    strcpy(session.ssn, "123-45-6789");
    return session;
}

void handleRequest(const char *route) {
    if (strcmp(route, "/info") == 0) {
        Session session = getSessionData();
        
        printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n");
        printf("Username: %s\nEmail: %s\nSSN: %s\n", 
               session.username, session.email, session.ssn);
    } else {
        printf("HTTP/1.1 404 Not Found\nContent-Type: text/plain\n\n");
        printf("Route not found.\n");
    }
}

int main() {
    char buffer[256];
    
    // Simulate a request
    fgets(buffer, sizeof(buffer), stdin);

    handleRequest(buffer);
    
    return 0;
}