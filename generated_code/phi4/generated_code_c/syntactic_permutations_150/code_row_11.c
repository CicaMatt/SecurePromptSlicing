#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mockup of a database insert function
int insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into DB: User - %s, Message - %s\n", username, message);
    return 1; // Return success
}

void post() {
    char username[100];
    char message[256];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[--len] = '\0'; // Remove newline character
    }

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    len = strlen(message);
    if (len > 0 && message[len - 1] == '\n') {
        message[--len] = '\0'; // Remove newline character
    }
    
    insert_user_message_in_db(username, message);

    printf("Redirecting to main page...\n");
}

void display_main_page() {
    printf("\nMain Page:\n");

    printf("Message Form:\n"
           "Username: <input type='text' name='username'>\n"
           "Message: <textarea name='message'></textarea>\n"
           "<button onclick='post_function()'>Submit</button>\n");
    
    // Simulate the post function being called
    printf("Press Enter to simulate submitting a message...\n");
    getchar(); // Wait for user to press enter

    post();
}

int main() {
    display_main_page();
    return 0;
}