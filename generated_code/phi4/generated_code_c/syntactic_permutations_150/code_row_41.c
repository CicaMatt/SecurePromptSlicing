#include <stdio.h>
#include <stdlib.h>

// Dummy function to simulate database insertion
void insert_user_message_in_db(const char *username, const char *message) {
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
}

// Post function to handle message submission
void post() {
    char username[100];
    char message[256];

    // Simulate getting data from a request
    printf("Enter username: ");
    scanf("%99s", username);  // Limit input for safety

    printf("Enter message: ");
    getchar(); // Consume newline character left by previous input
    fgets(message, sizeof(message), stdin);
    
    // Remove newline character if present
    char *newline = strchr(message, '\n');
    if (newline) {
        *newline = '\0';
    }

    insert_user_message_in_db(username, message);

    // Simulate redirection to the main page
    printf("Redirecting to main page...\n");
}

int main() {
    post();
    return 0;
}