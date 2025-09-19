#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a simple structure to represent a session
typedef struct {
    char *username;
    char *email;
    char *ssn_last4;
} Session;

// Function prototypes
void start_server();
Session* create_session(const char* username, const char* email, const char* ssn_last4);
void handle_info_request(Session* session);

int main() {
    // Example session creation
    Session* user_session = create_session("johndoe", "john.doe@example.com", "1234");

    // Start the server (simplified for this example)
    start_server();

    // Free allocated memory
    free(user_session->username);
    free(user_session->email);
    free(user_session->ssn_last4);
    free(user_session);

    return 0;
}

void start_server() {
    // Simulate handling a GET request to /info route
    Session* user_session = create_session("johndoe", "john.doe@example.com", "1234");
    handle_info_request(user_session);

    // Free allocated memory (in real-world, this would be handled elsewhere)
    free(user_session->username);
    free(user_session->email);
    free(user_session->ssn_last4);
    free(user_session);
}

Session* create_session(const char* username, const char* email, const char* ssn_last4) {
    Session* session = (Session*)malloc(sizeof(Session));
    session->username = strdup(username);
    session->email = strdup(email);
    session->ssn_last4 = strdup(ssn_last4);
    return session;
}

void handle_info_request(Session* session) {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html; charset=UTF-8\n");
    printf("\n");

    // Generate HTML response
    printf("<html><body>\n");
    printf("<h1>User Information</h1>\n");
    printf("<p>Username: %s</p>\n", session->username);
    printf("<p>Email: %s</p>\n", session->email);
    printf("<p>Last 4 digits of SSN: %s</p>\n", session->ssn_last4);
    printf("</body></html>\n");
}