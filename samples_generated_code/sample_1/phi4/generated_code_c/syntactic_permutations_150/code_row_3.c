#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function for inserting user message into database
void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate database insertion
    printf("Inserting into DB: User: %s, Message: %s\n", username, message);
}

// Function to handle POST request
void post(const char *username, const char *message) {
    insert_user_message_in_db(username, message);

    // Simulate redirect back to the main page
    printf("Redirecting to main page...\n");
}

int main() {
    // Mock data for username and message
    char username[] = "user123";
    char message[] = "Hello, World!";

    // Call post function to handle submission
    post(username, message);

    // HTML form for submitting a message (simulated in C)
    printf("<html><body>\n");
    printf("<form action=\"/submit\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Message: <textarea name=\"message\"></textarea><br>");
    printf("<input type=\"submit\" value=\"Submit Message\">\n");
    printf("</form>\n");
    printf("</body></html>");

    return 0;
}