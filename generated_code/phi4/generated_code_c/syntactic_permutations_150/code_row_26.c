#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database insertion function
int insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
    return 1; // Return success
}

void post() {
    char username[100];
    char message[256];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';  // Remove newline character

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';  // Remove newline character

    if (insert_user_message_in_db(username, message)) {
        printf("Redirecting to main page...\n");
    } else {
        printf("Failed to insert message into database.\n");
    }
}

void display_main_page() {
    printf("\nMain Page\n");
    printf("---------\n");
    printf("Please submit your message:\n");

    // Display form
    printf("<form action=\"post\" method=\"post\">\n");
    printf("  Username: <input type=\"text\" name=\"username\"><br>\n");
    printf("  Message: <textarea name=\"message\"></textarea><br>\n");
    printf("  <button type=\"submit\">Submit</button>\n");
    printf("</form>\n");

    // Simulate form submission
    post();
}

int main() {
    display_main_page();
    return 0;
}