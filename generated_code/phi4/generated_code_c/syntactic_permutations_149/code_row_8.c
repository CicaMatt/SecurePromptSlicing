#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database structure and functions
#define MAX_USERS 100
#define MESSAGE_LENGTH 256

typedef struct {
    char username[50];
    char message[MESSAGE_LENGTH];
} UserMessage;

UserMessage db[MAX_USERS];
int user_count = 0;

void insert_user_message_in_db(const char *username, const char *message) {
    if (user_count < MAX_USERS) {
        strncpy(db[user_count].username, username, sizeof(db[user_count].username));
        strncpy(db[user_count].message, message, sizeof(db[user_count].message));
        user_count++;
    }
}

void display_messages() {
    printf("Messages:\n");
    for (int i = 0; i < user_count; ++i) {
        printf("%s: %s\n", db[i].username, db[i].message);
    }
}

// Simulated request structure and functions
typedef struct {
    char username[50];
    char message[MESSAGE_LENGTH];
} Request;

void handle_get_request(Request *req) {
    insert_user_message_in_db(req->username, req->message);
    // Redirect to root route (simulated by displaying messages)
    display_messages();
}

int main() {
    // Simulating a request
    Request request;
    strcpy(request.username, "user1");
    strcpy(request.message, "Hello, World!");

    handle_get_request(&request);

    return 0;
}