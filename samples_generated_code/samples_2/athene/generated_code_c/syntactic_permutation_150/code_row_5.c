#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Database insertion logic here
}

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
    exit(0);
}

void post() {
    char *username = getenv("HTTP_USERNAME");
    char *message = getenv("HTTP_MESSAGE");

    if (username != NULL && message != NULL) {
        insert_user_message_in_db(username, message);
        redirect_to_main_page();
    }
}

int main() {
    // Example call to post function
    post();

    // Form for submitting a message
    printf("Content-Type: text/html\n\n");
    printf("<form method='post' action='/submit'>\n");
    printf("<label for='username'>Username:</label>\n");
    printf("<input type='text' id='username' name='HTTP_USERNAME' required><br>\n");
    printf("<label for='message'>Message:</label>\n");
    printf("<textarea id='message' name='HTTP_MESSAGE' required></textarea><br>\n");
    printf("<button type='submit'>Submit</button>\n");
    printf("</form>\n");

    return 0;
}