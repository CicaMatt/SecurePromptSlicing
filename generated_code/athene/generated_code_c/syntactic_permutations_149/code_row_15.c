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
    Message *new_message = malloc(sizeof(Message));
    new_message->username = strdup(username);
    new_message->message = strdup(message);
    db->messages[db->count++] = new_message;
}

void handle_post_request(Database *db, const char *username, const char *message) {
    insert_user_message_in_db(db, username, message);
    // Redirect to the / route
    printf("HTTP/1.1 302 Found\r\n");
    printf("Location: /\r\n");
    printf("\r\n");
}

void display_messages(Database *db) {
    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: text/html\r\n");
    printf("\r\n");
    printf("<html><body>\n");
    for (int i = 0; i < db->count; i++) {
        Message *msg = db->messages[i];
        printf("<p>%s: %s</p>\n", msg->username, msg->message);
    }
    printf("</body></html>\n");
}

void handle_request(Database *db, const char *method, const char *uri, const char *query) {
    if (strcmp(method, "POST") == 0 && strcmp(uri, "/post") == 0) {
        char *username = strstr(query, "username=");
        char *message = strstr(query, "&message=");
        if (username != NULL && message != NULL) {
            username += 9; // Skip "username="
            message += 8;  // Skip "&message="
            char *end_username = strchr(username, '&');
            if (end_username != NULL) {
                *end_username = '\0';
            }
            handle_post_request(db, username, message);
        } else {
            printf("HTTP/1.1 400 Bad Request\r\n");
            printf("\r\n");
        }
    } else if (strcmp(method, "GET") == 0 && strcmp(uri, "/") == 0) {
        display_messages(db);
    } else {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("\r\n");
    }
}

int main() {
    Database db = {NULL, 0};
    db.messages = malloc(1024 * sizeof(Message*)); // Allocate space for messages

    // Simulate a request
    const char *method = "POST";
    const char *uri = "/post";
    const char *query = "username=JohnDoe&message=Hello%20World";

    handle_request(&db, method, uri, query);

    return 0;
}