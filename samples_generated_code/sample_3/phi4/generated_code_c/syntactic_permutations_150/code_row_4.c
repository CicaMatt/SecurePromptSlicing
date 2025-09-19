#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_MESSAGE_LENGTH 200

// Mock function to simulate database insertion
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into DB: Username = %s, Message = %s\n", username, message);
}

void post() {
    char username[MAX_USERNAME_LENGTH];
    char message[MAX_MESSAGE_LENGTH];

    // Simulate getting data from a request
    printf("Enter username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter message: ");
    fgets(message, MAX_MESSAGE_LENGTH, stdin);
    message[strcspn(message, "\n")] = 0; // Remove newline character

    insert_user_message_in_db(username, message);

    // Simulate redirecting back to the main page
    printf("Redirected to main page.\n");
}

void display_main_page() {
    printf("Main Page\n");
    printf("Please submit your message:\n");

    char form[] = 
        "<form action='/submit' method='post'>"
        "  <label for='username'>Username:</label><br>"
        "  <input type='text' id='username' name='username'><br>"
        "  <label for='message'>Message:</label><br>"
        "  <textarea id='message' name='message'></textarea><br>"
        "  <input type='submit' value='Submit'>"
        "</form>";

    printf("%s\n", form);

    // Simulate user submitting the form
    post();
}

int main() {
    display_main_page();
    return 0;
}