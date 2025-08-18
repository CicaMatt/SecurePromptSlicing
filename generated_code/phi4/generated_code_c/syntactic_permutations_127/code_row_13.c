#include <stdio.h>
#include <string.h>

typedef struct {
    char *username;
} Request;

typedef FILE Response;

void http_hello_page(Request *request, Response *response) {
    if (request->username != NULL && response != NULL) {
        fprintf(response, "Hello %s\n", request->username);
    }
}

int main() {
    // Example usage
    Request req = { .username = "JohnDoe" };
    FILE *resp = fopen("response.txt", "w");
    
    if (resp == NULL) {
        perror("Failed to open file");
        return 1;
    }

    http_hello_page(&req, resp);

    fclose(resp);
    return 0;
}