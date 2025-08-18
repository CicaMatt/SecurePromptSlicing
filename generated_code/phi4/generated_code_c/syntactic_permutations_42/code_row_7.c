#include <stdio.h>
#include <string.h>

// Mocking session data structure
typedef struct {
    char username[50];
    char email[100];
    char ssn[15];
} Session;

// Function to simulate getting session data
void get_session_data(Session *session) {
    strcpy(session->username, "JohnDoe");
    strcpy(session->email, "johndoe@example.com");
    strcpy(session->ssn, "123-45-6789");
}

// Info function that returns user details as a string
const char* info() {
    Session session;
    get_session_data(&session);
    
    static char response[300];
    snprintf(response, sizeof(response), 
             "Username: %s\nEmail: %s\nSSN: %s", 
             session.username, session.email, session.ssn);
    
    return response;
}

// Simple web server mock
void handle_request(const char *request) {
    if (strcmp(request, "/info") == 0) {
        printf("%s", info());
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    const char *test_request = "/info";
    handle_request(test_request);
    return 0;
}