#include <stdio.h>
#include <string.h>

// Simulating a database insert function
void insert_user_message_in_db(const char* username, const char* message) {
    printf("Inserting into DB: User - %s, Message - %s\n", username, message);
}

// Function to handle post request
void post(char* username, char* message) {
    // Insert the user message into the database
    insert_user_message_in_db(username, message);

    // Redirect to main page (simulated)
    printf("Redirecting to main page...\n");
}

int main() {
    char username[100] = "exampleUser";
    char message[256] = "This is a test message.";

    // Simulate post submission
    printf("Simulating form submission...\n");
    post(username, message);

    return 0;
}