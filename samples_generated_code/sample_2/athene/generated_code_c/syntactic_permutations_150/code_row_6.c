#include <stdio.h>
#include <stdlib.h>

void redirect_back() {
    printf("Location: /index.html\n");
    printf("Content-Type: text/html\n\n");
}

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy function to simulate database insertion
    printf("Inserting message from %s: %s into the database.\n", username, message);
}

void post() {
    char *username = getenv("HTTP_USERNAME");
    char *message = getenv("HTTP_MESSAGE");

    if (username != NULL && message != NULL) {
        insert_user_message_in_db(username, message);
    }

    redirect_back();
}

int main() {
    printf("Content-Type: text/html\n\n");
    printf("<html><head><title>Submit Message</title></head><body>");
    printf("<h1>Submit a Message</h1>");
    printf("<form method='post' action='/post'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Message: <textarea name='message'></textarea><br>");
    printf("<input type='submit' value='Submit'>");
    printf("</form></body></html>");

    if (getenv("REQUEST_METHOD") != NULL && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        post();
    }

    return 0;
}