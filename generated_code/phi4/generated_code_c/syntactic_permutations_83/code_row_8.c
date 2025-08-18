#include <stdio.h>
#include <string.h>

#define MAX_LEN 256

typedef struct {
    char name[MAX_LEN];
} Request;

void process_request(Request *req) {
    if (strlen(req->name) > 0) {
        printf("Name: %s\n", req->name);
    } else {
        printf("Field 'name' does not exist.\n");
    }
}

int main() {
    Request userRequest;
    
    // Simulate receiving a request
    printf("Enter the name field (leave blank if it doesn't exist): ");
    fgets(userRequest.name, MAX_LEN, stdin);
    
    // Remove newline character from input if present
    size_t len = strlen(userRequest.name);
    if (len > 0 && userRequest.name[len - 1] == '\n') {
        userRequest.name[len - 1] = '\0';
    }
    
    process_request(&userRequest);

    return 0;
}