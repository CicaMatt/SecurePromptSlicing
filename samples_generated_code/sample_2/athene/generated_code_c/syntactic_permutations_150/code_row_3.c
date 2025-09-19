#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy implementation for database insertion
}

void post() {
    char username[100];
    char message[500];

    // Simulate getting the username and message from a request
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form method='post' action='/post'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Message: <textarea name='message'></textarea><br>");
    printf("<input type='submit' value='Submit'>");
    printf("</form>");

    // For demonstration, we'll read from stdin to simulate a POST request
    if (fgets(username, sizeof(username), stdin) && fgets(message, sizeof(message), stdin)) {
        insert_user_message_in_db(username, message);
        printf("Message submitted successfully. Redirecting...");
        printf("<meta http-equiv='refresh' content='0;url=/'>");
    } else {
        printf("Error: Failed to read username or message.");
    }
    printf("</body></html>");
}

int main() {
    post();
    return 0;
}