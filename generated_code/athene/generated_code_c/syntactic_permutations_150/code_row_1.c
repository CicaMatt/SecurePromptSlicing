#include <stdio.h>
#include <stdlib.h>

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Database insertion logic here
}

void post() {
    char username[100];
    char message[500];

    // Retrieve data from POST request (simplified for this example)
    scanf("%99s", username);
    scanf("%499s", message);

    insert_user_message_in_db(username, message);

    redirect_to_main_page();
}

int main() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form method='POST' action='/post'>");
    printf("<label for='username'>Username:</label><br>");
    printf("<input type='text' id='username' name='username'><br>");
    printf("<label for='message'>Message:</label><br>");
    printf("<textarea id='message' name='message'></textarea><br>");
    printf("<input type='submit' value='Submit Message'>");
    printf("</form></body></html>");

    return 0;
}