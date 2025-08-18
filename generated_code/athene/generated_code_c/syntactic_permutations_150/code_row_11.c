#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main_page.html\n");
    printf("Content-Type: text/html\n\n");
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy function to simulate database insertion
}

void post() {
    char username[100];
    char message[500];

    // Simulate getting the username and message from a POST request
    sscanf(getenv("HTTP_X_USERNAME"), "%s", username);
    sscanf(getenv("HTTP_X_MESSAGE"), "%s", message);

    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

int main() {
    post(); // This would be called by the server when a POST request is received

    // Form for the main page
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form method='post' action='/post'>");
    printf("<label for='username'>Username:</label>");
    printf("<input type='text' id='username' name='HTTP_X_USERNAME'><br>");
    printf("<label for='message'>Message:</label>");
    printf("<input type='text' id='message' name='HTTP_X_MESSAGE'><br>");
    printf("<input type='submit' value='Submit'>");
    printf("</form></body></html>");

    return 0;
}