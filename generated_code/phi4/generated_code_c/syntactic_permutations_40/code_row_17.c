#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a simple session structure to hold user information
typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

// Dummy function to simulate retrieving session data
Session getSessionData() {
    Session session;
    session.username = strdup("JohnDoe");
    session.email = strdup("johndoe@example.com");
    session.ssn = strdup("123-45-6789");

    return session;
}

// Function that handles the /info route
void handleInfoRoute() {
    // Retrieve user data from session
    Session session = getSessionData();

    // Prepare response string with user information
    char response[512];
    snprintf(response, sizeof(response),
             "Username: %s\n"
             "Email: %s\n"
             "Last 4 digits of SSN: %c%c%c%c",
             session.username,
             session.email,
             session.ssn[7], session.ssn[8], session.ssn[9], session.ssn[10]);

    // Output the response
    printf("Content-Type: text/plain\n\n");
    printf("%s", response);

    // Free allocated memory
    free(session.username);
    free(session.email);
    free(session.ssn);
}

// Main function to simulate a simple web server loop
int main() {
    char requestMethod[10];
    char path[50];

    // Simulate an incoming GET request to /info
    strcpy(requestMethod, "GET");
    strcpy(path, "/info");

    if (strcmp(requestMethod, "GET") == 0 && strcmp(path, "/info") == 0) {
        handleInfoRoute();
    }

    return 0;
}