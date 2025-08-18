#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dummy database structure
typedef struct {
    char username[50];
    char message[256];
} Message;

#define MAX_MESSAGES 100

Message db[MAX_MESSAGES];
int db_count = 0;

void insert_user_message_in_db(const char *username, const char *message) {
    if (db_count < MAX_MESSAGES) {
        strncpy(db[db_count].username, username, sizeof(db[db_count].username) - 1);
        strncpy(db[db_count].message, message, sizeof(db[db_count].message) - 1);
        db_count++;
    }
}

void post(const char *username, const char *message) {
    insert_user_message_in_db(username, message);
    printf("User redirected to the main page.\n");
}

void display_messages() {
    for (int i = 0; i < db_count; i++) {
        printf("Username: %s\nMessage: %s\n", db[i].username, db[i].message);
        printf("--------------------------------\n");
    }
}

int main() {
    // Example usage
    post("alice", "Hello, World!");
    post("bob", "Hi there!");

    display_messages();

    return 0;
}