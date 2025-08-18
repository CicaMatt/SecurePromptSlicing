#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulating a database insertion function
void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy implementation for demonstration purposes
    printf("Inserting into DB: User - %s, Message - %s\n", username, message);
}

// Function to handle the POST request
void post() {
    char *username = getenv("HTTP_USERNAME");
    char *message = getenv("HTTP_MESSAGE");

    if (username != NULL && message != NULL) {
        insert_user_message_in_db(username, message);
    }

    // Redirecting back to the main page
    printf("Content-Type: text/html\n\n");
    printf("<html><head><meta http-equiv=\"refresh\" content=\"0; url=/\"></head></html>");
}

// Simulating a main function to demonstrate form and post handling
int main() {
    char *request_method = getenv("REQUEST_METHOD");

    if (request_method != NULL && strcmp(request_method, "POST") == 0) {
        post();
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<form action=\"\" method=\"post\">");
        printf("Username: <input type=\"text\" name=\"username\"><br>");
        printf("Message: <textarea name=\"message\"></textarea><br>");
        printf("<input type=\"submit\" value=\"Submit\">");
        printf("</form>");
        printf("</body></html>");
    }

    return 0;
}