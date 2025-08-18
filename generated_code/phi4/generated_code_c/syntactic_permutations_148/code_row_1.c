#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mockup of a simple database insertion function.
void insert_user_message_in_db(const char *username, const char *message) {
    // For demonstration purposes, we'll just print out that a message was inserted.
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
}

// Function to handle user post submission
void post() {
    char username[50];
    char message[256];

    // Simulating retrieving data from a request (e.g., form submission).
    printf("Enter username: ");
    scanf("%49s", username);  // Use %49s to prevent buffer overflow

    printf("Enter message: ");
    getchar();  // Consume the newline character left by previous scanf
    fgets(message, sizeof(message), stdin);
    size_t len = strlen(message);
    if (len > 0 && message[len - 1] == '\n') {
        message[--len] = '\0';  // Remove trailing newline from fgets
    }

    insert_user_message_in_db(username, message);

    // Redirect to main page (simulation)
    printf("Redirecting to the main page...\n");
}

// Function to display messages
void display_messages() {
    // For demonstration purposes, let's assume we have some static data.
    const char *messages[] = {
        "Alice: Hello World!",
        "Bob: Hi there!",
        "Charlie: How's everyone doing?"
    };
    int num_messages = sizeof(messages) / sizeof(messages[0]);

    printf("Displaying messages:\n");
    for (int i = 0; i < num_messages; ++i) {
        printf("%s\n", messages[i]);
    }
}

// Main function
int main() {
    char choice;
    
    while (1) {
        printf("\nMenu:\n");
        printf("1. Post a message\n");
        printf("2. Display messages\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        
        choice = getchar();
        getchar();  // Consume newline character

        switch (choice) {
            case '1':
                post();
                break;
            case '2':
                display_messages();
                break;
            case '3':
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0; // This line will never be reached
}