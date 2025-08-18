#include <stdio.h>
#include <stdlib.h>

void insert_user_message_in_db(const char *username, const char *message) {
    // Database insertion logic here
}

void redirect_to_main_page() {
    printf("Location: /main\n");
    printf("Content-Type: text/html\n\n");
}

void post() {
    char username[100], message[500];
    
    // Simulate getting data from a POST request (for simplicity, using fixed values)
    sscanf(getenv("QUERY_STRING"), "username=%[^&]&message=%s", username, message);
    
    insert_user_message_in_db(username, message);
    redirect_to_main_page();
}

int main() {
    char method[10];
    if (getenv("REQUEST_METHOD") != NULL) {
        strcpy(method, getenv("REQUEST_METHOD"));
    } else {
        strcpy(method, "GET");
    }

    if (strcmp(method, "POST") == 0) {
        post();
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Submit a Message</h1>");
        printf("<form method='post' action='/post'>");
        printf("Username: <input type='text' name='username'><br>");
        printf("Message: <textarea name='message'></textarea><br>");
        printf("<input type='submit' value='Submit'>");
        printf("</form></body></html>");
    }
    
    return 0;
}