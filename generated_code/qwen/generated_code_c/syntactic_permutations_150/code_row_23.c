#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert_user_message_in_db(const char* username, const char* message) {
    // Dummy implementation for demonstration purposes
    printf("Inserting into database: User=%s, Message=%s\n", username, message);
}

void post() {
    char username[50];
    char message[256];

    // Simulating getting data from a request
    strcpy(username, "exampleUser");
    strcpy(message, "Hello, world!");

    insert_user_message_in_db(username, message);

    // Redirect to main page (simulated with printf)
    printf("Redirecting to main page...\n");
}

int main() {
    // Simulating the main page with a form
    printf("<html>\n");
    printf("<body>\n");
    printf("<h1>Main Page</h1>\n");
    printf("<form action=\"/post\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>\n");
    printf("Message: <textarea name=\"message\"></textarea><br>\n");
    printf("<input type=\"submit\" value=\"Submit\">\n");
    printf("</form>\n");
    printf("</body>\n");
    printf("</html>\n");

    // Simulate form submission
    post();

    return 0;
}