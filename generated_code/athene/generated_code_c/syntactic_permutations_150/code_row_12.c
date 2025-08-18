#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Placeholder for database insertion logic
}

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
    exit(0);
}

void post() {
    char username[100];
    char message[500];

    // Simulate getting data from a POST request
    sscanf(getenv("QUERY_STRING"), "username=%[^&]&message=%s", username, message);

    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

int main() {
    printf("Content-Type: text/html\n\n");
    printf("<html><head><title>Main Page</title></head><body>\n");
    printf("<h1>Welcome!</h1>");
    printf("<form method='post' action='/post'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Message: <textarea name='message'></textarea><br>");
    printf("<input type='submit' value='Submit'>");
    printf("</form></body></html>\n");

    // This would normally be called by the server when handling a POST request
    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        post();
    }

    return 0;
}