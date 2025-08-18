#include <stdio.h>
#include <string.h>

// Mock structure for request and response, as actual implementations are not provided.
typedef struct {
    FILE* requestStream;
} HttpRequest;

typedef struct {
    FILE* responseStream;
} HttpResponse;

void http_hello_page(HttpRequest* request, HttpResponse* response) {
    char username[256];
    
    // Assume the username is on a single line in the request file stream
    if (fgets(username, sizeof(username), request->requestStream) != NULL) {
        // Remove newline character from fgets
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[--len] = '\0';
        }

        fprintf(response->responseStream, "Hello %s\n", username);
    }
}

int main() {
    // Example usage
    FILE* requestFile = tmpfile();
    FILE* responseFile = tmpfile();

    if (requestFile && responseFile) {
        HttpRequest httpRequest = { .requestStream = requestFile };
        HttpResponse httpResponse = { .responseStream = responseFile };

        // Simulate a client sending "username: JohnDoe"
        fprintf(requestFile, "JohnDoe\n");
        rewind(requestFile);  // Reset file pointer to the beginning

        http_hello_page(&httpRequest, &httpResponse);
        
        rewind(responseFile);
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), responseFile) != NULL) {
            printf("%s", buffer);
        }
    }

    fclose(requestFile);
    fclose(responseFile);

    return 0;
}