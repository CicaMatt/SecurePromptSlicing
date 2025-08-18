#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[50];
    char message[256];
} UserMessage;

int insert_user_message_in_db(const char *username, const char *message) {
    // Simulate insertion into a database.
    printf("Inserting message from %s: %s\n", username, message);
    return 1; // Return success
}

void display_messages() {
    static int count = 0;
    UserMessage messages[10];
    if (count == 0) {
        strcpy(messages[0].username, "Alice");
        strcpy(messages[0].message, "Hello World!");
        count++;
    }
    
    printf("Displaying Messages:\n");
    for (int i = 0; i < count; i++) {
        printf("%s: %s\n", messages[i].username, messages[i].message);
    }
}

void handle_post_request(const char *username, const char *message) {
    if (insert_user_message_in_db(username, message)) {
        printf("Redirecting to / route...\n");
        display_messages();
    } else {
        printf("Failed to insert message.\n");
    }
}

int main() {
    // Simulate handling a POST request
    const char *username = "Bob";
    const char *message = "Hi, this is Bob!";
    
    handle_post_request(username, message);
    
    return 0;
}