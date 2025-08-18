#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database structure and functions
typedef struct {
    char username[50];
    char message[256];
} Message;

Message db[100];
int db_count = 0;

void insert_user_message_in_db(const char* username, const char* message) {
    if (db_count < 100) {
        strcpy(db[db_count].username, username);
        strcpy(db[db_count].message, message);
        db_count++;
    }
}

void handle_submit(char* username, char* user_message) {
    insert_user_message_in_db(username, user_message);
    printf("Redirecting to main page...\n");
}

void display_messages() {
    printf("Displaying messages:\n");
    for (int i = 0; i < db_count; i++) {
        printf("User: %s\nMessage: %s\n", db[i].username, db[i].message);
    }
}

// Simulated function to handle user input
void simulate_user_input() {
    char username[50] = "user1";
    char message[256] = "Hello World!";
    
    handle_submit(username, message);

    // Display all messages in the database
    display_messages();
}

int main() {
    simulate_user_input();
    return 0;
}