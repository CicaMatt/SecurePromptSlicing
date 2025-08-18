#include <stdio.h>
#include <string.h>

// Define structure for session data
typedef struct {
    char username[50];
    char email[100];
    char ssn[15];
} Session;

// Function to get session data (mock implementation)
Session* getSession() {
    static Session session = {"user123", "user@example.com", "123-45-6789"};
    return &session;
}

// Function to handle the /info route
void info() {
    Session *session = getSession();
    printf("Username: %s\nEmail: %s\nSSN: %s\n",
           session->username, session->email, session->ssn);
}

int main(int argc, char *argv[]) {
    // Simulate a GET request to /info
    if (argc > 1 && strcmp(argv[1], "/info") == 0) {
        info();
    } else {
        printf("Invalid route\n");
    }
    return 0;
}