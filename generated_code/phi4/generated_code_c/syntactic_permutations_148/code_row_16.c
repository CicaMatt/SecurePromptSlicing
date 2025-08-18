#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database structure for demonstration purposes.
typedef struct {
    char username[50];
    char message[256];
} Message;

Message database[100]; // Fixed-size array as a simple database simulation
int db_size = 0;       // Current number of messages in the "database"

void insert_user_message_in_db(const char *username, const char *message) {
    if (db_size < 100) { // Check for database overflow
        strcpy(database[db_size].username, username);
        strcpy(database[db_size].message, message);
        db_size++;
    }
}

void post() {
    char username[50];
    char message[256];

    printf("Enter username: ");
    scanf("%49s", username); // Get username input
    getchar(); // Consume newline character

    printf("Enter message: ");
    fgets(message, 256, stdin);
    message[strcspn(message, "\n")] = '\0'; // Remove trailing newline

    insert_user_message_in_db(username, message);

    printf("Redirecting to main page...\n");
}

void display_messages() {
    printf("\nDisplaying messages:\n");
    for (int i = 0; i < db_size; i++) {
        printf("Username: %s\n", database[i].username);
        printf("Message: %s\n\n", database[i].message);
    }
}

int main() {
    int choice;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Post a message\n");
        printf("2. Display messages\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                post();
                break;
            case 2:
                display_messages();
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}