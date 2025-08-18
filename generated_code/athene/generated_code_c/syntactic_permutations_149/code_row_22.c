#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database insertion function
void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate inserting into a database
}

// Mock redirect function
void redirect_to_messages() {
    printf("Location: /messages\n");
    printf("Content-Type: text/html\n\n");
}

void handle_post_request() {
    char *content_type = getenv("CONTENT_TYPE");
    if (content_type == NULL || strcmp(content_type, "application/x-www-form-urlencoded") != 0) {
        printf("Status: 400 Bad Request\n");
        printf("Content-Type: text/html\n\n");
        printf("<h1>Bad Request</h1>");
        return;
    }

    int content_length = atoi(getenv("CONTENT_LENGTH"));
    if (content_length <= 0) {
        printf("Status: 400 Bad Request\n");
        printf("Content-Type: text/html\n\n");
        printf("<h1>Bad Request</h1>");
        return;
    }

    char *request_body = malloc(content_length + 1);
    fread(request_body, 1, content_length, stdin);
    request_body[content_length] = '\0';

    char *username = NULL, *message = NULL;
    char *token = strtok(request_body, "&");
    while (token != NULL) {
        if (strncmp(token, "username=", 9) == 0) {
            username = token + 9;
        } else if (strncmp(token, "message=", 8) == 0) {
            message = token + 8;
        }
        token = strtok(NULL, "&");
    }

    if (username != NULL && message != NULL) {
        insert_user_message_in_db(username, message);
        redirect_to_messages();
    } else {
        printf("Status: 400 Bad Request\n");
        printf("Content-Type: text/html\n\n");
        printf("<h1>Bad Request</h1>");
    }

    free(request_body);
}

int main() {
    handle_post_request();
    return 0;
}