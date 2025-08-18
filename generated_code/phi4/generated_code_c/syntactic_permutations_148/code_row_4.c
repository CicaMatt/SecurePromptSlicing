#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mocking a simple database with an array of structs
typedef struct {
    char username[50];
    char message[256];
} UserMessage;

#define MAX_MESSAGES 100

UserMessage db[MAX_MESSAGES];
int db_index = 0;

void insert_user_message_in_db(const char *username, const char *message) {
    if (db_index < MAX_MESSAGES) {
        strncpy(db[db_index].username, username, sizeof(db[0].username));
        db[db_index].username[sizeof(db[0].username) - 1] = '\0';
        strncpy(db[db_index].message, message, sizeof(db[0].message));
        db[db_index].message[sizeof(db[0].message) - 1] = '\0';
        db_index++;
    } else {
        printf("Database is full.\n");
    }
}

void define() {
    char username[50];
    char message[256];

    // Simulate getting data from a request
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0'; // Remove newline character

    insert_user_message_in_db(username, message);

    // Redirect to main page
    printf("\nRedirecting to main page...\n");
}

void display_messages() {
    printf("\n--- Messages ---\n");
    for (int i = 0; i < db_index; i++) {
        printf("User: %s\nMessage: %s\n", db[i].username, db[i].message);
        printf("----------------\n");
    }
}

int main() {
    int choice;
    do {
        printf("\n1. Submit Message\n2. Display Messages\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character left by scanf

        switch (choice) {
            case 1:
                define();
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