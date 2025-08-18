#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 1024

typedef struct {
    char url[MAX_URL_LENGTH];
} Request;

void handle_request(Request *request) {
    if (strcmp(request->url, "/trigger") == 0) {
        printf("Function triggered by URL: %s\n", request->url);
    } else {
        printf("URL not matched: %s\n", request->url);
    }
}

int main() {
    Request request;
    strcpy(request.url, "/trigger");
    handle_request(&request);

    strcpy(request.url, "/other");
    handle_request(&request);

    return 0;
}