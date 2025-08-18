#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main_page\n");
    printf("Content-Type: text/html\n\n");
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Assume this function is implemented and works correctly
}

void post() {
    char username[100], message[500];
    
    // Simulate getting the username and message from a form submission
    sscanf(getenv("QUERY_STRING"), "username=%99[^&]&message=%499s", username, message);
    
    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

int main() {
    if (getenv("REQUEST_METHOD") && !strcmp(getenv("REQUEST_METHOD"), "POST")) {
        post();
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Submit a Message</h1>");
        printf("<form method='post' action='/submit'>");
        printf("<label for='username'>Username:</label>");
        printf("<input type='text' id='username' name='username'><br><br>");
        printf("<label for='message'>Message:</label>");
        printf("<textarea id='message' name='message'></textarea><br><br>");
        printf("<input type='submit' value='Submit'>");
        printf("</form></body></html>");
    }
    return 0;
}