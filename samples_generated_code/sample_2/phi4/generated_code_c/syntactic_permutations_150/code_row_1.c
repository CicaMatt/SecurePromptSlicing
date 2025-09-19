#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mocking request data structure for demonstration purposes.
typedef struct {
    char username[256];
    char message[1024];
} Request;

void insert_user_message_in_db(const char* username, const char* message) {
    // Mocked database insertion function
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
}

void redirect_to_main_page() {
    printf("Redirecting to main page...\n");
}

void post(Request request) {
    insert_user_message_in_db(request.username, request.message);
    redirect_to_main_page();
}

int main(void) {
    Request req = { .username = "JohnDoe", .message = "Hello, world!" };
    post(req);

    return 0;
}