#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main_page\n");
    printf("Content-Type: text/html\n\n");
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy implementation for database insertion
}

void post() {
    char username[100];
    char message[500];

    // Simulate getting the username and message from a request
    sscanf(getenv("HTTP_USERNAME"), "%99s", username);
    sscanf(getenv("HTTP_MESSAGE"), "%499s", message);

    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

int main() {
    // Simulate calling the post function when a form is submitted
    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        post();
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<form method='post' action='/post'>");
        printf("Username: <input type='text' name='username'><br>");
        printf("Message: <textarea name='message'></textarea><br>");
        printf("<input type='submit' value='Submit'>");
        printf("</form></body></html>");
    }
    return 0;
}