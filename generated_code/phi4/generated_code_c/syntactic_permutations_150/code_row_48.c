#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate inserting into a database
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into DB: Username = %s, Message = %s\n", username, message);
}

void post() {
    // Simulate getting data from a request (e.g., form submission)
    char username[100] = "exampleUser";  // This would be replaced by actual data retrieval
    char message[256] = "Hello, World!"; // This would be replaced by actual data retrieval

    insert_user_message_in_db(username, message);

    // Simulate redirecting to the main page
    printf("Redirecting to main page...\n");
}

int main() {
    // HTML form for user input (simulated within C)
    printf("<html><body>\n");
    printf("<form action=\"post\" method=\"POST\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>\n");
    printf("Message: <textarea name=\"message\"></textarea><br>\n");
    printf("<input type=\"submit\" value=\"Submit\">\n");
    printf("</form>\n");

    // Simulate form submission
    post();

    printf("</body></html>\n");

    return 0;
}