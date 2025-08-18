#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated structure for a message record
typedef struct {
    char username[50];
    char message[256];
} MessageRecord;

// Function prototypes
void insert_user_message_in_db(const char *username, const char *message);
void display_messages();
char* get_input(const char* prompt);

int main() {
    // Get user input for the username and message
    char *username = get_input("Enter username: ");
    char *user_message = get_input("Enter your message: ");

    // Insert the message into a simulated database (file)
    insert_user_message_in_db(username, user_message);

    // Display all messages from the "database"
    display_messages();

    free(username);
    free(user_message);

    // Simulate redirection by returning to the main menu
    printf("Redirecting to / route...\n");
    
    return 0;
}

void insert_user_message_in_db(const char *username, const char *message) {
    FILE *file = fopen("messages.txt", "a");
    if (file == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    
    fprintf(file, "%s: %s\n", username, message);
    fclose(file);
}

void display_messages() {
    char line[512];
    FILE *file = fopen("messages.txt", "r");
    if (file == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    
    printf("\nMessages:\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
}

char* get_input(const char* prompt) {
    size_t buffer_size = 256;
    char *buffer = malloc(buffer_size);

    if (!buffer) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("%s", prompt);
        fgets(buffer, buffer_size, stdin);

        // Remove newline character
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        // Check for empty input and re-prompt if necessary
        if (strlen(buffer) > 0) {
            break;
        }
        printf("Input cannot be empty. Please try again.\n");
    }

    return buffer;
}