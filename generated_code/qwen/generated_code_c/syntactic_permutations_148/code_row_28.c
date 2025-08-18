#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert_user_message_in_db(const char* username, const char* message) {
    // Dummy implementation for demonstration purposes
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
}

void redirect_to_display_messages() {
    // Dummy implementation for demonstration purposes
    printf("Redirecting to display messages...\n");
}

void post(const char* request) {
    const char* username = "dummyUser"; // Extract from request in real scenario
    const char* message = "dummyMessage"; // Extract from request in real scenario

    insert_user_message_in_db(username, message);
    redirect_to_display_messages();
}

int main() {
    const char* fakeRequest = "user=dummyUser&message=dummyMessage";
    post(fakeRequest);
    return 0;
}