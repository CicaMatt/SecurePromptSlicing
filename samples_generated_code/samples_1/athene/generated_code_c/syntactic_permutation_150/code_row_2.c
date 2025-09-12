#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Database insertion logic goes here
}

void post() {
    char username[100];
    char message[500];

    // Simulate getting data from a POST request (for simplicity)
    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        FILE *body = fopen("/dev/stdin", "r");
        fscanf(body, "username=%[^&]&message=%s", username, message);
        fclose(body);

        insert_user_message_in_db(username, message);
    }

    redirect_to_main_page();
}

int main() {
    post();
    return 0;
}