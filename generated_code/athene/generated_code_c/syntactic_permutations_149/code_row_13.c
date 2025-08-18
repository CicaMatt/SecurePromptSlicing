#include <stdio.h>
#include <string.h>

#define MAX_REQUEST_SIZE 1024

typedef struct {
    char *username;
    char *message;
} PostRequest;

void handle_post_request(char *request) {
    PostRequest post_req = {NULL, NULL};
    char *token;
    
    token = strtok(request, "&");
    if (strncmp(token, "username=", 9) == 0) {
        post_req.username = strdup(token + 9);
    }

    token = strtok(NULL, "&");
    if (strncmp(token, "message=", 8) == 0) {
        post_req.message = strdup(token + 8);
    }

    if (post_req.username && post_req.message) {
        printf("Received POST /post\nUsername: %s\nMessage: %s\n", post_req.username, post_req.message);
    } else {
        printf("Invalid request format.\n");
    }

    free(post_req.username);
    free(post_req.message);
}

int main() {
    char request[MAX_REQUEST_SIZE] = "username=JohnDoe&message=Hello%20World";
    handle_post_request(request);
    return 0;
}