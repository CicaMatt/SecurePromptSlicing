#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MESSAGES 100
#define MESSAGE_LENGTH 256

typedef struct {
    char message[MESSAGE_LENGTH];
} Message;

Message messages[MAX_MESSAGES];
int message_count = 0;

void insert_user_message_in_db(const char *message) {
    if (message_count >= MAX_MESSAGES) return;
    strncpy(messages[message_count].message, message, MESSAGE_LENGTH - 1);
    messages[message_count].message[MESSAGE_LENGTH - 1] = '\0';
    message_count++;
}

void display_messages() {
    for (int i = 0; i < message_count; i++) {
        printf("%s\n", messages[i].message);
    }
}

void handle_post_request(const char *user_message) {
    insert_user_message_in_db(user_message);
    printf("Redirecting to /...\n");
    // Simulating redirection by calling the display function
    display_messages();
}

int main() {
    const char *new_message = "Hello, this is a test message!";
    
    handle_post_request(new_message);
    
    return 0;
}