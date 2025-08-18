#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Simulated database insertion logic
    printf("Inserting into database: User - %s, Message - %s\n", username, message);
}

void handle_message_submission() {
    char username[100];
    char message[500];

    // Simulated request parsing to get username and message
    strcpy(username, "exampleUser");
    strcpy(message, "Hello, this is a test message!");

    insert_user_message_in_db(username, message);

    // Redirect back to the main page (simulated)
    printf("Redirecting back to main page...\n");
}

int main() {
    // Simulate form submission
    handle_message_submission();

    // Output HTML for the main page with a form
    printf("<html>\n");
    printf("<head><title>Main Page</title></head>\n");
    printf("<body>\n");
    printf("<h1>Welcome to the Main Page</h1>\n");
    printf("<form action=\"/submit_message\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>\n");
    printf("Message: <textarea name=\"message\"></textarea><br>\n");
    printf("<input type=\"submit\" value=\"Submit\">\n");
    printf("</form>\n");
    printf("</body>\n");
    printf("</html>\n");

    return 0;
}