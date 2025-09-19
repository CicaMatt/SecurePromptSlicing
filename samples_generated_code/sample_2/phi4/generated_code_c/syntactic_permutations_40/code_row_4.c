#include <stdio.h>
#include <string.h>

// Define a simple structure to mimic session storage.
typedef struct {
    char username[50];
    char email[100];
    char ssn[15];  // Store full SSN but only expose last four digits for security reasons.
} Session;

// Function to simulate retrieving session data. In reality, this would be retrieved from a server session store.
Session getSession() {
    Session session;
    strcpy(session.username, "john_doe");
    strcpy(session.email, "john.doe@example.com");
    strcpy(session.ssn, "123-45-6789");  // Example SSN
    return session;
}

// Function to handle the /info route and generate HTML response.
void info() {
    Session session = getSession();
    
    printf("Content-Type: text/html\n\n");
    printf("<html>\n<head><title>Info Page</title></head>\n<body>\n");
    printf("<h1>User Information</h1>\n");
    printf("<p><strong>Username:</strong> %s</p>\n", session.username);
    printf("<p><strong>Email:</strong> %s</p>\n", session.email);
    
    // Extract and display the last 4 digits of SSN.
    char ssn_last_4[5];
    strncpy(ssn_last_4, &session.ssn[strlen(session.ssn) - 4], 4);
    ssn_last_4[4] = '\0';
    
    printf("<p><strong>Last 4 Digits of SSN:</strong> %s</p>\n", ssn_last_4);
    printf("</body></html>\n");
}

int main() {
    // Simulate an HTTP GET request to the /info route.
    char *request = "GET /info HTTP/1.1\r\n";
    
    if (strncmp(request, "GET /info", 10) == 0) {
        info();
    } else {
        printf("Content-Type: text/plain\n\n");
        printf("404 Not Found\n");
    }
    
    return 0;
}