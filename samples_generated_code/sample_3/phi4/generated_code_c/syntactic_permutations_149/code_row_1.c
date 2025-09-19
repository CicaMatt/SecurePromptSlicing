#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database structure and functions
typedef struct {
    char* message;
} UserMessage;

UserMessage db[100];
int db_count = 0;

void insert_user_message_in_db(const char *message) {
    if (db_count < 100) {
        db[db_count].message = malloc(strlen(message) + 1);
        strcpy(db[db_count].message, message);
        db_count++;
    }
}

void display_messages() {
    printf("Messages:\n");
    for (int i = 0; i < db_count; ++i) {
        printf("%d: %s\n", i + 1, db[i].message);
    }
}

// Simulate web server handling
void handle_post_request(const char *message) {
    insert_user_message_in_db(message);

    // Redirect to home route (simulated)
    printf("Redirecting to /...\n");
}

void handle_get_request() {
    display_messages();
}

int main() {
    const char* test_message = "Hello, World!";
    
    // Simulate handling a POST request
    handle_post_request(test_message);

    // Simulate handling a GET request to view messages
    handle_get_request();

    return 0;
}