#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char username[1024];
    if (fgets(username, sizeof(username), request) != NULL) {
        // Remove newline character from username if present
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }
        fprintf(response, "Hello %s", username);
    }
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (request == NULL || response == NULL) {
        perror("Error opening files");
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}