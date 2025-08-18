#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100

void http_hello_page(FILE *request, FILE *response) {
    char username[MAX_USERNAME_LENGTH];
    
    if (fgets(username, sizeof(username), request) != NULL) {
        // Remove newline character if present
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }
        
        fprintf(response, "Hello %s", username);
    } else {
        fprintf(response, "Hello Guest");
    }
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (!request || !response) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}