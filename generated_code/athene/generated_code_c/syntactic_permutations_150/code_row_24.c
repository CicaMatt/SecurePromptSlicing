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

    // Simulate getting values from a POST request (form data)
    sscanf(getenv("QUERY_STRING"), "username=%[^&]&message=%s", username, message);

    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

int main() {
    if (getenv("REQUEST_METHOD") && !strcmp(getenv("REQUEST_METHOD"), "POST")) {
        post();
    } else {
        // Display the form for submitting a message
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<form method='post' action='/submit'>");
        printf("Username: <input type='text' name='username'><br>");
        printf("Message: <textarea name='message'></textarea><br>");
        printf("<input type='submit' value='Submit'>");
        printf("</form></body></html>");
    }
    return 0;
}