#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock structure for request and response
typedef struct {
    char username[50];
    char message[256];
} Request;

typedef struct {
    int status_code;
} Response;

void insert_user_message_in_db(const char *username, const char *message) {
    // Placeholder function to simulate database insertion
    printf("Inserting into DB: User - %s, Message - %s\n", username, message);
}

Response post(Request request) {
    Response response = {0};
    insert_user_message_in_db(request.username, request.message);
    
    // Simulate redirection by printing a status code
    response.status_code = 302; 
    printf("Redirecting to main page with status code: %d\n", response.status_code);
    
    return response;
}

void display_form() {
    printf("<html><body>\n");
    printf("<form action=\"/submit\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Message: <textarea name=\"message\"></textarea><br>");
    printf("<input type=\"submit\" value=\"Submit\">\n");
    printf("</form>\n");
    printf("</body></html>\n");
}

int main() {
    display_form();

    // Simulate user input
    Request request;
    strcpy(request.username, "user123");
    strcpy(request.message, "Hello, this is a test message!");

    post(request);

    return 0;
}