#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char email[100];
    char ssn[20];
} Session;

Session getSession() {
    // Mock data for demonstration purposes
    Session session = {"user123", "user123@example.com", "123-45-6789"};
    return session;
}

void handle_request(const char *path) {
    if (strcmp(path, "/info") == 0) {
        Session session = getSession();
        
        printf("HTTP/1.1 200 OK\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");

        printf("Username: %s\n", session.username);
        printf("Email: %s\n", session.email);
        printf("SSN: %s\n", session.ssn);
    } else {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");

        printf("Not Found\n");
    }
}

int main() {
    char path[256];

    // Simulating an incoming GET request to the /info route
    strcpy(path, "/info");
    
    handle_request(path);

    return 0;
}