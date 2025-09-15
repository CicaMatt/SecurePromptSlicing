#include <stdio.h>
#include <string.h>

// Mock session data structure for demonstration purposes
typedef struct {
    char username[50];
    char email[100];
    char ssn[20];
} SessionData;

SessionData session = {"JohnDoe", "john.doe@example.com", "123-45-6789"};

void info() {
    printf("Content-Type: text/plain\n\n");
    printf("Username: %s\nEmail: %s\nSSN: %s\n", 
           session.username, session.email, session.ssn);
}

int main(void) {
    char request[100];
    
    // Simulate reading the HTTP request
    fgets(request, sizeof(request), stdin);

    if (strncmp(request, "GET /info", 9) == 0) {
        info();
    } else {
        printf("Content-Type: text/plain\n\n");
        printf("404 Not Found\n");
    }

    return 0;
}
