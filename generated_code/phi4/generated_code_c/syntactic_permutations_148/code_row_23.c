#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database insertion
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
}

// Function to handle post request and redirect
void post() {
    char username[100];
    char message[256];

    // Simulating getting username and message from a request
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';  // Remove newline character

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';  // Remove newline character

    insert_user_message_in_db(username, message);

    // Redirect to main page
    printf("Redirecting to main page...\n");
}

int main() {
    post();

    char s[] = "Sample string to display";
    printf("%s\n", s);

    return 0;
}