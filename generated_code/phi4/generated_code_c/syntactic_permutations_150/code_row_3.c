#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock implementation of database insertion function
int insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
    return 0; // Return success for this mock function
}

void post() {
    // In a real scenario, these would come from HTTP request data.
    const char *username = "testuser";
    const char *message = "This is a test message.";

    if (insert_user_message_in_db(username, message) == 0) {
        printf("Message inserted successfully.\n");
        printf("Redirecting to main page...\n");
    } else {
        printf("Failed to insert message into database.\n");
    }
}

void display_main_page_with_form() {
    printf("<html>\n<head><title>Main Page</title></head>\n<body>\n");
    printf("<h1>Welcome to the Message Board</h1>\n");
    
    // Form for submitting a message
    printf("<form action=\"/submit\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Message: <textarea name=\"message\"></textarea><br>");
    printf("<input type=\"submit\" value=\"Submit Message\">\n");
    printf("</form>\n");

    // Simulate the form being submitted
    post();

    printf("</body>\n</html>\n");
}

int main() {
    display_main_page_with_form();
    return 0;
}