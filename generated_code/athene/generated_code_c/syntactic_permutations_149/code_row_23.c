#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock functions for demonstration purposes
void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate inserting into a database
}

void redirect_to_root() {
    printf("HTTP/1.1 302 Found\r\n");
    printf("Location: /\r\n");
    printf("\r\n");
}

void handle_post_request() {
    char *content_type = getenv("CONTENT_TYPE");
    if (content_type == NULL || strcmp(content_type, "application/x-www-form-urlencoded") != 0) {
        printf("HTTP/1.1 400 Bad Request\r\n");
        printf("\r\n");
        return;
    }

    int content_length = atoi(getenv("CONTENT_LENGTH"));
    char *request_body = (char *)malloc(content_length + 1);
    fread(request_body, 1, content_length, stdin);
    request_body[content_length] = '\0';

    char username[100], message[500];
    sscanf(request_body, "username=%[^&]&message=%s", username, message);

    insert_user_message_in_db(username, message);
    redirect_to_root();

    free(request_body);
}