#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

int main() {
    char request[BUFFER_SIZE];
    FILE *requestFile = fopen("request.txt", "r");
    FILE *responseFile = fopen("response.txt", "w");

    if (requestFile == NULL || responseFile == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read the username from the request
    fgets(request, BUFFER_SIZE, requestFile);
    
    // Remove newline character if present
    size_t len = strlen(request);
    if (len > 0 && request[len - 1] == '\n') {
        request[len - 1] = '\0';
    }

    char username[BUFFER_SIZE];
    sscanf(request, "%s", username);

    // Construct and write the response
    fprintf(responseFile, "Hello %s\n", username);

    fclose(requestFile);
    fclose(responseFile);

    return 0;
}