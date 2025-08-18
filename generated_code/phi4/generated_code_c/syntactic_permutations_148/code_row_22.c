#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *message;
} Message;

void insert_user_message_in_db(const char *username, const char *message) {
    // Simulated database insertion logic (for demonstration purposes)
    printf("Inserting into DB: %s -> %s\n", username, message);
}

void post() {
    char username[100];
    char message[256];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0'; // Remove newline character

    insert_user_message_in_db(username, message);

    // Redirect user to main page (simulation)
    printf("\nRedirecting to main page...\n");
}

void display_messages() {
    // Simulated retrieval from database
    Message messages[] = {
        {"Alice", "Hello World!"},
        {"Bob", "Hi there!"},
        {"Charlie", "C programming is fun!"}
    };

    int count = sizeof(messages) / sizeof(messages[0]);

    printf("\nMessages:\n");
    for (int i = 0; i < count; ++i) {
        printf("User: %s, Message: %s\n", messages[i].username, messages[i].message);
    }
}

int main() {
    int choice;
    do {
        printf("\n1. Post a message\n2. Display messages\n3. Exit\nChoose an option: ");
        scanf("%d%*c", &choice); // %*c to consume the newline character

        switch (choice) {
            case 1:
                post();
                break;
            case 2:
                display_messages();
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}