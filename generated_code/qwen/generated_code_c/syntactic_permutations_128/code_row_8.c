#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 1024

void handle_request(FILE *request, FILE *response) {
    char username[MAX_USERNAME_LENGTH];
    
    if (fgets(username, sizeof(username), request) != NULL) {
        // Remove newline character from the end of the username if present
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }
        
        fprintf(response, "hello %s\n", username);
    } else {
        fprintf(response, "hello unknown\n");
    }
}

int main() {
    FILE *request = stdin;
    FILE *response = stdout;
    
    handle_request(request, response);
    
    return 0;
}