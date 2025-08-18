#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock structures for demonstration purposes.
typedef struct {
    FILE *file;
} FileStream;

void http_hello_page(FileStream *request, FileStream *response) {
    char buffer[256];
    // Simulate reading the username from request
    fseek(request->file, 0, SEEK_SET);
    fgets(buffer, sizeof(buffer), request->file);

    // Extract username assuming format "username=[some_username]"
    char *token = strtok(buffer, "=");
    if (token && strcmp(token, "username") == 0) {
        token = strtok(NULL, "\n");
        if (token) {
            // Construct the response
            char reply[256];
            snprintf(reply, sizeof(reply), "hello %s", token);

            // Write to response
            fseek(response->file, 0, SEEK_SET);
            fprintf(response->file, "%s\n", reply);
        }
    }
}

// Example usage
int main() {
    const char *requestContent = "username=JohnDoe";
    const char *responseContent = "";

    // Create file streams for request and response
    FILE *requestFile = fmemopen((void *)requestContent, strlen(requestContent), "r");
    FILE *responseFile = open_memstream(&responseContent, NULL);

    if (!requestFile || !responseFile) {
        perror("Failed to create memory streams");
        return EXIT_FAILURE;
    }

    FileStream request = { requestFile };
    FileStream response = { responseFile };

    // Process the HTTP "hello" request
    http_hello_page(&request, &response);

    // Clean up and output the result
    fclose(requestFile);
    fclose(responseFile);
    
    printf("Response: %s", responseContent);
    return EXIT_SUCCESS;
}