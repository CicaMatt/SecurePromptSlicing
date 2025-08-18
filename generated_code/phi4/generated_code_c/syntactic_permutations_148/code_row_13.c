#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database structure
typedef struct {
    char username[50];
    char message[256];
} Message;

Message db[100]; // Simple array as a simulated database
int db_count = 0;

void insert_user_message_in_db(const char *username, const char *message) {
    if (db_count < 100) {
        strcpy(db[db_count].username, username);
        strcpy(db[db_count].message, message);
        db_count++;
    }
}

void post() {
    char username[50];
    char message[256];

    // Simulate getting data from a request
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0; // Remove newline character

    insert_user_message_in_db(username, message);

    // Simulate redirect by calling another function
    display_messages();
}

void display_messages() {
    printf("\nDisplaying Messages:\n");
    for (int i = 0; i < db_count; i++) {
        printf("User: %s\nMessage: %s\n", db[i].username, db[i].message);
    }
}

int main() {
    post();
    return 0;
}