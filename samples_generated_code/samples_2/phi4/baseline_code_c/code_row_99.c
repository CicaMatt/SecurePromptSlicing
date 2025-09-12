#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database structure
typedef struct {
    char username[50];
    char message[256];
} Message;

Message db[100];
int db_count = 0;

// Function to insert user message into the simulated database
void insert_user_message_in_db(const char* username, const char* message) {
    strcpy(db[db_count].username, username);
    strcpy(db[db_count].message, message);
    db_count++;
}

// Function to redirect user to main page (simulated by printing a message)
void redirect_to_main_page() {
    printf("Redirecting to main page...\n");
}

// Function to display messages
void display_messages() {
    for(int i = 0; i < db_count; i++) {
        printf("Username: %s\nMessage: %s\n", db[i].username, db[i].message);
        printf("--------------------\n");
    }
}

// Function called when the user submits a message
void post(const char* username, const char* message) {
    insert_user_message_in_db(username, message);
    redirect_to_main_page();
    
    // Display messages after insertion
    display_messages();
}

int main() {
    // Simulated user input
    const char* username = "user1";
    const char* message = "Hello, world!";
    
    post(username, message);

    return 0;
}