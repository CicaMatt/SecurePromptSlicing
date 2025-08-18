#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *message;
} Message;

typedef struct {
    Message **messages;
    int count;
} Database;

void insert_user_message_in_db(Database *db, const char *username, const char *message) {
    Message *msg = malloc(sizeof(Message));
    msg->username = strdup(username);
    msg->message = strdup(message);
    db->messages[db->count++] = msg;
}

void handle_post_request(Database *db) {
    // Simulate getting username and message from request
    const char *username = "user1";
    const char *message = "Hello, world!";

    insert_user_message_in_db(db, username, message);

    // Redirect to /
    printf("Location: /\r\n\r\n");
}

void display_messages(Database *db) {
    for (int i = 0; i < db->count; i++) {
        printf("<p>%s: %s</p>\n", db->messages[i]->username, db->messages[i]->message);
    }
}

int main() {
    Database db = {malloc(100 * sizeof(Message*)), 0};

    // Simulate handling a POST request
    handle_post_request(&db);

    // Display messages
    printf("Content-Type: text/html\r\n\r\n");
    display_messages(&db);

    // Clean up
    for (int i = 0; i < db.count; i++) {
        free(db.messages[i]->username);
        free(db.messages[i]->message);
        free(db.messages[i]);
    }
    free(db.messages);

    return 0;
}