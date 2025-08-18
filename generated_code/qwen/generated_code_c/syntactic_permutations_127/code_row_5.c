#include <stdio.h>
#include <string.h>

int main() {
    FILE *request_file = fopen("request.txt", "r");
    FILE *response_file = fopen("response.txt", "w");

    if (request_file == NULL || response_file == NULL) {
        perror("Failed to open files");
        return 1;
    }

    char username[256];
    if (fgets(username, sizeof(username), request_file) != NULL) {
        // Remove newline character if present
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }
        
        fprintf(response_file, "Hello %s", username);
    } else {
        perror("Failed to read from request file");
    }

    fclose(request_file);
    fclose(response_file);

    return 0;
}