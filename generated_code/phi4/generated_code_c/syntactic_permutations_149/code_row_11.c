#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database structure for demonstration purposes.
typedef struct {
    char **messages;
    int count;
} Database;

Database db = {NULL, 0};

void initialize_database() {
    db.messages = NULL;
    db.count = 0;
}

int insert_user_message_in_db(const char *username, const char *message) {
    // Allocate memory for new message.
    char **new_messages = realloc(db.messages, sizeof(char*) * (db.count + 1));
    if (!new_messages) return -1;

    // Create the full message string.
    size_t len = strlen(username) + strlen(message) + 2; // extra space for colon and null terminator
    char *full_message = malloc(len);
    if (!full_message) {
        free(new_messages);
        return -1;
    }
    
    snprintf(full_message, len, "%s: %s", username, message);

    // Store the new full message in the database.
    db.messages = new_messages;
    db.messages[db.count] = full_message;
    db.count++;

    return 0;
}

void display_messages() {
    printf("Messages:\n");
    for (int i = 0; i < db.count; ++i) {
        if (db.messages[i]) {
            printf("%s\n", db.messages[i]);
        }
    }
}

// Mock function to redirect to the root route.
void redirect_to_root() {
    printf("\nRedirecting to /...\n");
}

int main(int argc, char *argv[]) {
    initialize_database();

    if (argc > 3 && strcmp(argv[1], "post") == 0) {
        // Example usage: ./program post Alice Hello World!
        const char *username = argv[2];
        char *message = argv[3];
        for (int i = 4; i < argc; ++i) {
            message = realloc(message, strlen(message) + strlen(argv[i]) + 2);
            strcat(message, " ");
            strcat(message, argv[i]);
        }

        if (insert_user_message_in_db(username, message) == 0) {
            free(message);
            redirect_to_root();
        } else {
            printf("Failed to insert message.\n");
        }
    } else {
        display_messages();
    }
    
    // Free allocated memory
    for (int i = 0; i < db.count; ++i) {
        free(db.messages[i]);
    }
    free(db.messages);

    return 0;
}