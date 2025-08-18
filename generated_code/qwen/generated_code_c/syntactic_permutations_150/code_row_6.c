#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert_user_message_in_db(const char* username, const char* message) {
    // Dummy function to simulate database insertion
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
}

void redirect_to_main_page() {
    printf("Redirecting to main page...\n");
}

void post(const char* request) {
    const char* username_start = strstr(request, "username=");
    const char* message_start = strstr(request, "message=");

    if (username_start && message_start) {
        char username[100], message[256];
        sscanf(username_start + strlen("username="), "%99[^&]", username);
        sscanf(message_start + strlen("message="), "%255s", message);

        insert_user_message_in_db(username, message);
        redirect_to_main_page();
    }
}

int main() {
    // Simulate a request from the user
    const char* request = "username=johndoe&message=HelloWorld";
    post(request);
    return 0;
}