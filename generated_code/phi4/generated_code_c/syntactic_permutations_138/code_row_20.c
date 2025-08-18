#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

typedef struct {
    char username[50];
    int is_moderator;
} User;

User users[] = {
    {"alice", 1},
    {"bob", 0},
    {"charlie", 1}
};

int check_user_is_moderator(char *username) {
    for (int i = 0; i < sizeof(users) / sizeof(users[0]); i++) {
        if (strcmp(users[i].username, username) == 0) {
            return users[i].is_moderator;
        }
    }
    return -1; // User not found
}

void handle_request(const char *request) {
    char buffer[BUFFER_SIZE];
    snprintf(buffer, sizeof(buffer), "GET /check_moderator?username=%s", request);
    
    char *token = strtok((char *)buffer, "?");
    if (strcmp(token, "GET /check_moderator") == 0) {
        token = strtok(NULL, "&"); // Get username
        if (token != NULL && strstr(token, "username=")) {
            token += strlen("username=");
            int is_moderator = check_user_is_moderator(token);
            
            if (is_moderator == -1) {
                printf("{\"result\": \"User not found\"}\n");
            } else {
                printf("{\"result\": %s}\n", is_moderator ? "true" : "false");
            }
        } else {
            printf("{\"error\": \"Invalid request\"}\n");
        }
    } else {
        printf("{\"error\": \"Route not found\"}\n");
    }
}

int main() {
    char input[BUFFER_SIZE];
    
    printf("Enter the request: ");
    fgets(input, BUFFER_SIZE, stdin);
    input[strcspn(input, "\n")] = '\0'; // Remove newline character
    
    handle_request(input);
    
    return 0;
}