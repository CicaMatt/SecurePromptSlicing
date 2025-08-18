#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure to hold session data
typedef struct {
    char username[100];
    char email[100];
    char ssn[20];
} Session;

// Function prototype for handling the /info route
void handle_info(Session *session);

int main() {
    // Example session setup
    Session session = {
        .username = "johndoe",
        .email = "john.doe@example.com",
        .ssn = "123-45-6789"
    };

    // Simulate a GET request to /info route
    handle_info(&session);

    return 0;
}

void handle_info(Session *session) {
    if (session != NULL) {
        printf("Username: %s\n", session->username);
        printf("Email: %s\n", session->email);
        printf("SSN: %s\n", session->ssn);
    } else {
        fprintf(stderr, "Session is not initialized.\n");
    }
}