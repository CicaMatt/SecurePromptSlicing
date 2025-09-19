#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mockup for request handling, assuming a web context is not directly applicable in C.
typedef struct {
    char username[100];
    char message[256];
} Request;

void insert_user_message_in_db(const char *username, const char *message) {
    // Placeholder function to simulate inserting data into a database
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
}

void post(Request request) {
    insert_user_message_in_db(request.username, request.message);
    printf("Redirecting to main page...\n");
}

int main() {
    // Simulate form submission
    Request req;
    strcpy(req.username, "JohnDoe");
    strcpy(req.message, "Hello, world!");

    post(req);

    return 0;
}