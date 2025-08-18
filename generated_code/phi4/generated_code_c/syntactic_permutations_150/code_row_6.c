#include <stdio.h>
#include <stdlib.h>

// Mock function for inserting user message in the database
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into DB: Username = %s, Message = %s\n", username, message);
}

// Function to handle form submission
void define_post_function() {
    char username[100];
    char message[256];

    // Simulate getting data from request (e.g., POST request)
    printf("Enter username: ");
    scanf("%99s", username);  // Using %99s to prevent buffer overflow
    printf("Enter message: ");
    scanf(" %[^\n]s", message);  // Using space before %[^\n]s to consume any leading whitespace

    insert_user_message_in_db(username, message);

    // Redirect user back to main page (simulated)
    printf("Redirecting to main page...\n");
}

int main() {
    printf("Main Page\n");
    printf("Submit your message:\n");

    // Simulate form submission
    define_post_function();

    return 0;
}