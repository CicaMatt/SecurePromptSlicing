#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main_page.html\r\n");
    printf("\r\n");
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy function to simulate database insertion
}

void post() {
    char username[100];
    char message[500];

    // Simulate getting the username and message from a request
    sscanf(getenv("HTTP_X_USERNAME"), "%99s", username);
    sscanf(getenv("HTTP_X_MESSAGE"), "%499s", message);

    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

int main() {
    // Simulate a CGI environment for testing purposes
    setenv("HTTP_X_USERNAME", "testuser", 1);
    setenv("HTTP_X_MESSAGE", "Hello, world!", 1);

    post();

    return 0;
}